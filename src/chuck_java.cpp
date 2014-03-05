// for usleep
#define _XOPEN_SOURCE    500
#include <unistd.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#if HAVE_CONFIG_H
#include "../config.h"
#endif

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
            // run chuck in a separate thread that attaches itself to the JVM
            // and detaches when its done
            VMThreadImpl vmThread;

        public:
            ChuckJavaImpl(Chuck * ck, JNIEnv * jenv) : m_ck(ck), m_jenv(jenv) {}

            // Make the JNIEnv public so it can be accessed from vmThread
            JNIEnv * m_jenv;

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
                return m_ck->RunVM();
            }

            // kill the chuck vm and compiler
            void Destroy() {
                assert(m_ck);
                m_ck->Destroy();
            }

            // wait for the chuck vm thread to finish
            bool Wait() {
                return vmThread.Wait();
            }
        };

        bool Create(ChuckJava ** ckj, JNIEnv * jenv) {
            Chuck * ck;
            bool createdChuck = chuck::Create(&ck);
            assert(ck);
            *ckj = new ChuckJavaImpl(ck, jenv);
            return createdChuck;
        }

        class JIntReceiverImpl : public JIntReceiver {
        private:
            // cached reference to the JNINativeInterface
            JNIEnv * m_env;
            // cached reference to the JavaVM
            JavaVM * m_jvm;
            // cached reference to the object used to invoke the given receive method
            jobject m_obj;
            // cached reference to the receive method
            jmethodID m_receive;

            virtual ~JIntReceiverImpl() {
                assert(m_env);
                m_env->DeleteGlobalRef(m_obj);
            }
        public:
            JIntReceiverImpl(JNIEnv * env, jobject obj, jmethodID receive)
                : m_env(env), m_receive(receive) {
                m_env->GetJavaVM(&m_jvm);
                m_obj = m_env->NewGlobalRef(obj);
            }
            // receive value from chuck and relay to java
            void receive(long val) {
                m_env->CallVoidMethod(m_obj, m_receive, (jlong) val);
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
            JNIEnv * m_env;
            // cached reference to the JavaVM
            JavaVM * m_jvm;
            // cached reference to the object used to invoke the given receive method
            jobject m_obj;
            // cached reference to the receive method
            jmethodID m_receive;

            virtual ~JFloatReceiverImpl() {
                assert(m_env);
                m_env->DeleteGlobalRef(m_obj);
            }

        public:
            JFloatReceiverImpl(JNIEnv * env, jobject obj, jmethodID receive)
                : m_env(env), m_receive(receive) {
                m_env->GetJavaVM(&m_jvm);
                m_obj = m_env->NewGlobalRef(obj);
            }
            // receive value from chuck and relay to java
            void receive(double val) {
                m_env->CallVoidMethod(m_obj, m_receive, (jdouble) val);
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
            JNIEnv * m_env;
            // cached reference to the JavaVM
            JavaVM * m_jvm;
            // cached reference to the object used to invoke the given receive method
            jobject m_obj;
            // cached reference to the receive method
            jmethodID m_receive;

            virtual ~JStringReceiverImpl() {
                assert(m_env);
                m_env->DeleteGlobalRef(m_obj);
            }

        public:
            JStringReceiverImpl(JNIEnv * env, jobject obj, jmethodID receive)
                : m_env(env), m_receive(receive) {
                m_env->GetJavaVM(&m_jvm);
                m_obj = m_env->NewGlobalRef(obj);
            }
            // receive value from chuck and relay to java
            void receive(const char * val) {
                jstring str = m_env->NewStringUTF(val);
                m_env->CallVoidMethod(m_obj, m_receive, str);
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

            JNIEnv * jenv = chuckj->m_jenv;
            JavaVM * jvm;
            jenv->GetJavaVM(&jvm);

            assert(jvm);

            if (JNI_OK != jvm->AttachCurrentThread((void **) &jenv, NULL)) {
                fprintf(stderr, "could not attach chuck thread to jvm\n");
                exit(EXIT_FAILURE);
            }

            // blocking call to run the chuck vm
            chuckj->RunVM();

            chuckj->Destroy();

            // clear all the events
            evs->Clear();

            if (JNI_OK != jvm->DetachCurrentThread()) {
                fprintf(stderr, "could not detach chuck thread from jvm\n");
                exit(EXIT_FAILURE);
            }

            return (void *) 1;
        }

        bool VMThreadImpl::Wait() {
            return chuck_thread.wait(-1, false);
        }

    } // namespace java
} // namespace chuck

#endif // ENABLE_JAVA
