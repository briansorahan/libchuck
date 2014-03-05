// for usleep
#define _XOPEN_SOURCE    500
#include <unistd.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../config.h"

#include "chuck_def.h"
#include "chuck_java.h"
#include "util_events.h"
#include "util_thread.h"

#if ENABLE_JAVA

#include <jni.h>

namespace chuck {
    namespace java {

        /*
         * This particular thread class will attach the chuck thread to the JVM.
         */
        class VMThreadImpl : public VMThread {
        public:
            // spawns thread
            void Run(Chuck * ckj);
            // wait for chuck
            bool Wait();

        private:
            XThread chuck_thread;
            // thread function
            static void * RunChuck(void * arg);
        };

        class ChuckJavaImpl : public ChuckJava {
        private:
            Chuck * m_ck;
            JNIEnv * m_jenv;

            // run chuck in a separate thread that attaches itself to the JVM
            // and detaches when its done
            VMThreadImpl vmThread;

        public:
            ChuckJavaImpl(Chuck * ck, JNIEnv * jenv) : m_ck(ck), m_jenv(jenv) {}

            bool SporkFile(const char * file) {
                return m_ck->SporkFile(file);
            }

            // spork some files
            bool Spork(unsigned int files, const char ** filenames) {
                assert(m_ck);

                int i;
                for (i = 0; i < files; i++) {
                    if (! SporkFile(filenames[i])) return false;
                }

                vmThread.Run(this);

                usleep(500);
                return true;
            }

            // yield the current thread to the chuck vm
            bool RunVM() {
                assert(m_ck);
                bool ranVM = m_ck->RunVM();
                return ranVM;
            }

            // kill the chuck vm and compiler
            void Destroy() {
                assert(m_ck);
                m_ck->Destroy();
            }

            // wait for the chuck vm thread to finish
            bool Wait() {
                bool success = vmThread.Wait();
                return success;
            }
        };

        bool Create(ChuckJava ** ckj, JNIEnv * jenv) {
            Chuck * ck;
            bool createdChuck = chuck::Create(&ck);
            assert(ck);
            *ckj = new ChuckJavaImpl(ck, jenv);
            return createdChuck;
        }

        /*
         * Note that for the java Receiver classes, we cannot invoke a
         * java callback (i.e. the "receive" method) from a native thread.
         * (You get 'FATAL ERROR in native method: Using JNIEnv in non-Java thread')
         * I have been unable to find a way to reliably attach/detach the current
         * native thread to the jvm outside of the receive methods below.
         * Supposedly the way I am doing it below is a big performance drain, but
         * if this is proven in the wild then we can pursue optimization.
         *
         * Another thing to consider is that attaching/detaching the native thread
         * invoking the receive callbacks may require knowledge of the internal
         * threading of chuck. If this is the case, then this optimization could be
         * difficult to implement correctly.
         */

        class JIntReceiverImpl : public JIntReceiver {
        private:
            // cached reference to the JNINativeInterface
            JNIEnv * m_jenv;
            // cached reference to the JavaVM
            JavaVM * m_jvm;
            // cached reference to the object used to invoke the given receive method
            jobject m_obj;
            // cached reference to the receive method
            jmethodID m_receive;

            virtual ~JIntReceiverImpl() {
                assert(m_jenv);
                m_jenv->DeleteGlobalRef(m_obj);
            }
        public:
            JIntReceiverImpl(JNIEnv * env, jobject obj, jmethodID receive)
                : m_jenv(env), m_receive(receive) {
                m_jenv->GetJavaVM(&m_jvm);
                m_obj = m_jenv->NewGlobalRef(obj);
            }
            // receive value from chuck and relay to java
            void receive(long val) {
                assert(m_jvm);

                if (JNI_OK != m_jvm->AttachCurrentThread((void **) &m_jenv, NULL)) {
                    fprintf(stderr, "could not attach chuck thread to jvm\n");
                    exit(EXIT_FAILURE);
                }

                m_jenv->CallVoidMethod(m_obj, m_receive, (jlong) val);

                assert(m_jvm);
                if (JNI_OK != m_jvm->DetachCurrentThread()) {
                    fprintf(stderr, "could not detach chuck thread from jvm\n");
                    exit(EXIT_FAILURE);
                }
            }
        };

        JIntReceiver * JIntReceiver::Create(JNIEnv * env, jobject obj) {
            jclass c = env->GetObjectClass(obj);
            jmethodID receive = env->GetMethodID(c, "receive", "(J)V");

            if (c == NULL) {
                fprintf(stderr, "could not get class of IntReceiver\n");
                exit(EXIT_FAILURE);
            }

            if (receive == NULL) {
                fprintf(stderr, "could not find receive method of IntReceiver\n");
                exit(EXIT_FAILURE);
            }

            return new JIntReceiverImpl(env, obj, receive);
        }

        class JFloatReceiverImpl : public JFloatReceiver {
        private:
            // cached reference to the JNINativeInterface
            JNIEnv * m_jenv;
            // cached reference to the JavaVM
            JavaVM * m_jvm;
            // cached reference to the object used to invoke the given receive method
            jobject m_obj;
            // cached reference to the receive method
            jmethodID m_receive;

            virtual ~JFloatReceiverImpl() {
                assert(m_jenv);
                m_jenv->DeleteGlobalRef(m_obj);
            }

        public:
            JFloatReceiverImpl(JNIEnv * env, jobject obj, jmethodID receive)
                : m_jenv(env), m_receive(receive) {
                m_jenv->GetJavaVM(&m_jvm);
                m_obj = m_jenv->NewGlobalRef(obj);
            }
            // receive value from chuck and relay to java
            void receive(double val) {
                assert(m_jvm);

                if (JNI_OK != m_jvm->AttachCurrentThread((void **) &m_jenv, NULL)) {
                    fprintf(stderr, "could not attach chuck thread to jvm\n");
                    exit(EXIT_FAILURE);
                }

                m_jenv->CallVoidMethod(m_obj, m_receive, (jdouble) val);

                assert(m_jvm);
                if (JNI_OK != m_jvm->DetachCurrentThread()) {
                    fprintf(stderr, "could not detach chuck thread from jvm\n");
                    exit(EXIT_FAILURE);
                }
            }
        };

        JFloatReceiver * JFloatReceiver::Create(JNIEnv * env, jobject obj) {
            jclass c = env->GetObjectClass(obj);
            jmethodID receive = env->GetMethodID(c, "receive", "(D)V");
            return new JFloatReceiverImpl(env, obj, receive);
        }

        class JStringReceiverImpl : public JStringReceiver {
        private:
            // cached reference to the JNINativeInterface
            JNIEnv * m_jenv;
            // cached reference to the JavaVM
            JavaVM * m_jvm;
            // cached reference to the object used to invoke the given receive method
            jobject m_obj;
            // cached reference to the receive method
            jmethodID m_receive;

            virtual ~JStringReceiverImpl() {
                assert(m_jenv);
                m_jenv->DeleteGlobalRef(m_obj);
            }

        public:
            JStringReceiverImpl(JNIEnv * env, jobject obj, jmethodID receive)
                : m_jenv(env), m_receive(receive) {
                m_jenv->GetJavaVM(&m_jvm);
                m_obj = m_jenv->NewGlobalRef(obj);
            }
            // receive value from chuck and relay to java
            void receive(const char * val) {
                assert(m_jvm);

                if (JNI_OK != m_jvm->AttachCurrentThread((void **) &m_jenv, NULL)) {
                    fprintf(stderr, "could not attach chuck thread to jvm\n");
                    exit(EXIT_FAILURE);
                }

                jstring str = m_jenv->NewStringUTF(val);
                m_jenv->CallVoidMethod(m_obj, m_receive, str);

                assert(m_jvm);
                if (JNI_OK != m_jvm->DetachCurrentThread()) {
                    fprintf(stderr, "could not detach chuck thread from jvm\n");
                    exit(EXIT_FAILURE);
                }
            }
        };

        // factory method
        JStringReceiver * JStringReceiver::Create(JNIEnv * env, jobject obj) {
            jclass c = env->GetObjectClass(obj);
            jmethodID receive = env->GetMethodID(c, "receive", "(Ljava/lang/String;)V");
            return new JStringReceiverImpl(env, obj, receive);
        }


        void VMThreadImpl::Run(Chuck * ckj) {
            chuck_thread.start(&VMThreadImpl::RunChuck, (void *) ckj);
        }

        void * VMThreadImpl::RunChuck(void * arg) {
            ChuckJavaImpl * chuckj = (ChuckJavaImpl *) arg;
            Events * evs = Events::GetInstance();

            // blocking call to run the chuck vm
            chuckj->RunVM();

            chuckj->Destroy();

            // clear all the events
            evs->Clear();

            return (void *) 1;
        }

        bool VMThreadImpl::Wait() {
            return chuck_thread.wait(-1, false);
        }

    } // namespace java
} // namespace chuck

#endif // ENABLE_JAVA
