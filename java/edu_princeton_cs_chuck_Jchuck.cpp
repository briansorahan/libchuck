#include <assert.h>
#include <jni.h>
#include <stdio.h>

#include "handle.h"
#include "../src/chuck.h"
#include "edu_princeton_cs_chuck_Jchuck.h"
// #include "edu_princeton_cs_chuck_FloatReceiver.h"
// #include "edu_princeton_cs_chuck_IntReceiver.h"
// #include "edu_princeton_cs_chuck_StringReceiver.h"

using chuck::Chuck;

/*
 * Class:     edu_princeton_cs_chuck_Chuck
 * Method:    initialize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_edu_princeton_cs_chuck_Jchuck_initialize(JNIEnv * env, jobject obj) {
    // jchuck = new JChuck();
    Chuck * ck;
    chuck::Create(&ck);
    assert(ck);
    setHandle(env, obj, ck);
}

// JNI methods
JNIEXPORT jboolean JNICALL Java_edu_princeton_cs_chuck_Jchuck_spork(JNIEnv * env,
                                                                   jobject obj,
                                                                   jobjectArray files) {
    Chuck * ck = getHandle< Chuck >(env, obj);
    assert(ck);

    jsize numfiles = env->GetArrayLength(files);

    // convert files to char **
    const char * filenames[numfiles];

    int i;
    for (i = 0; i < numfiles; i++) {
        jstring filename = static_cast< jstring >(env->GetObjectArrayElement(files, i));
        if (NULL == filename) return false;

        const char * f = env->GetStringUTFChars(filename, NULL);
        if (NULL == f) return false;

        filenames[i] = f;
    }

    return ck->Spork((unsigned int) numfiles, filenames);
}

JNIEXPORT jboolean JNICALL Java_edu_princeton_cs_chuck_Jchuck_run(JNIEnv * env, jobject obj) {
    Chuck * ck = getHandle< Chuck >(env, obj);
    assert(ck);
    return ck->Run();
}

/*
 * Receiver classes relay chuck data from native code to java.
 */

class JIntReceiver : public chuck::IntReceiver {
private:
    // cached reference to the JNINativeInterface
    JNIEnv * m_env;
    // cached reference to the object used to invoke the given receive method
    jobject m_obj;
    // cached reference to the receive method
    jmethodID m_receive;
    // private constructor
    JIntReceiver(JNIEnv * env, jobject obj, jmethodID receive)
        : m_env(env), m_obj(obj), m_receive(receive) {
    }

public:
    // factory method
    static JIntReceiver * create(JNIEnv * env, jobject obj) {
        // TODO: determine signature string
        jclass c = env->GetObjectClass(obj);
        jmethodID receive = env->GetMethodID(c, "receive", "(J)V");
        return new JIntReceiver(env, obj, receive);
    }
    // receive value from chuck and relay to java
    void receive(long val) {
        m_env->CallVoidMethod(m_obj, m_receive, (jlong) val);
    }
};

class JFloatReceiver : public chuck::FloatReceiver {
private:
    // cached reference to the JNINativeInterface
    JNIEnv * m_env;
    // cached reference to the object used to invoke the given receive method
    jobject m_obj;
    // cached reference to the receive method
    jmethodID m_receive;
    // private constructor
    JFloatReceiver(JNIEnv * env, jobject obj, jmethodID receive)
        : m_env(env), m_obj(obj), m_receive(receive) {
    }

public:
    // factory method
    static JFloatReceiver * create(JNIEnv * env, jobject obj) {
        // TODO: determine signature string
        jclass c = env->GetObjectClass(obj);
        jmethodID receive = env->GetMethodID(c, "receive", "(D)V");
        return new JFloatReceiver(env, obj, receive);
    }
    // receive value from chuck and relay to java
    void receive(double val) {
        m_env->CallVoidMethod(m_obj, m_receive, (jdouble) val);
    }
};

class JStringReceiver : public chuck::StringReceiver {
private:
    // cached reference to the JNINativeInterface
    JNIEnv * m_env;
    // cached reference to the object used to invoke the given receive method
    jobject m_obj;
    // cached reference to the receive method
    jmethodID m_receive;
    // private constructor
    JStringReceiver(JNIEnv * env, jobject obj, jmethodID receive)
        : m_env(env), m_obj(obj), m_receive(receive) {
    }

public:
    // factory method
    static JStringReceiver * create(JNIEnv * env, jobject obj) {
        // TODO: determine signature string
        jclass c = env->GetObjectClass(obj);
        jmethodID receive = env->GetMethodID(c, "receive", "(Ljava/lang/String;)V");
        return new JStringReceiver(env, obj, receive);
    }
    // receive value from chuck and relay to java
    void receive(const char * val) {
        jstring str = m_env->NewStringUTF(val);
        m_env->CallVoidMethod(m_obj, m_receive, str);
    }
};

/*
 * Class:     edu_princeton_cs_chuck_Jchuck
 * Method:    sendTo
 * Signature: (Ljava/lang/String;J)V
 */
JNIEXPORT void JNICALL
Java_edu_princeton_cs_chuck_Jchuck_sendTo__Ljava_lang_String_2J(JNIEnv * env,
                                                                jobject obj,
                                                                jstring chan,
                                                                jlong val) {
    jboolean isCopy;
    const char * ch = env->GetStringUTFChars(chan, &isCopy);
    chuck::SendTo(ch, val);
}

/*
 * Class:     edu_princeton_cs_chuck_Jchuck
 * Method:    sendTo
 * Signature: (Ljava/lang/String;D)V
 */
JNIEXPORT void JNICALL
Java_edu_princeton_cs_chuck_Jchuck_sendTo__Ljava_lang_String_2D(JNIEnv * env,
                                                                jobject obj,
                                                                jstring chan,
                                                                jdouble val) {
    jboolean isCopy;
    const char * ch = env->GetStringUTFChars(chan, &isCopy);
    chuck::SendTo(ch, val);
}

/*
 * Class:     edu_princeton_cs_chuck_Jchuck
 * Method:    sendTo
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL
Java_edu_princeton_cs_chuck_Jchuck_sendTo__Ljava_lang_String_2Ljava_lang_String_2(JNIEnv * env,
                                                                                  jobject obj,
                                                                                  jstring chan,
                                                                                  jstring val) {
    jboolean chanIsCopy;
    jboolean valIsCopy;
    const char * ch = env->GetStringUTFChars(chan, &chanIsCopy);
    const char * v = env->GetStringUTFChars(val, &valIsCopy);
    chuck::SendTo(ch, v);
}

/*
 * Class:     edu_princeton_cs_chuck_Jchuck
 * Method:    receiveFrom
 * Signature: (Ljava/lang/String;Ledu/princeton/cs/chuck/Jchuck/IntReceiver;)V
 */
JNIEXPORT void JNICALL
Java_edu_princeton_cs_chuck_Jchuck_receiveFrom__Ljava_lang_String_2Ledu_princeton_cs_chuck_Jchuck_IntReceiver_2(JNIEnv * env, jobject obj, jstring chan, jobject receiver) {
    fprintf(stderr, "[libjchuck] registering int receiver");

    jboolean chanIsCopy;
    const char * ch = env->GetStringUTFChars(chan, &chanIsCopy);
    JIntReceiver * ir = JIntReceiver::create(env, receiver);
    chuck::RegisterIntReceiver(ch, ir);

    fprintf(stderr, "[libjchuck] registered int receiver");
}

/*
 * Class:     edu_princeton_cs_chuck_Jchuck
 * Method:    receiveFrom
 * Signature: (Ljava/lang/String;Ledu/princeton/cs/chuck/Jchuck/FloatReceiver;)V
 */
JNIEXPORT void JNICALL
Java_edu_princeton_cs_chuck_Jchuck_receiveFrom__Ljava_lang_String_2Ledu_princeton_cs_chuck_Jchuck_FloatReceiver_2(JNIEnv * env, jobject obj, jstring chan, jobject receiver) {
    jboolean chanIsCopy;
    const char * ch = env->GetStringUTFChars(chan, &chanIsCopy);
    JFloatReceiver * fr = JFloatReceiver::create(env, receiver);
    chuck::RegisterFloatReceiver(ch, fr);
}

/*
 * Class:     edu_princeton_cs_chuck_Jchuck
 * Method:    receiveFrom
 * Signature: (Ljava/lang/String;Ledu/princeton/cs/chuck/Jchuck/StringReceiver;)V
 */
JNIEXPORT void JNICALL
Java_edu_princeton_cs_chuck_Jchuck_receiveFrom__Ljava_lang_String_2Ledu_princeton_cs_chuck_Jchuck_StringReceiver_2(JNIEnv * env, jobject obj, jstring chan, jobject receiver) {
    jboolean chanIsCopy;
    const char * ch = env->GetStringUTFChars(chan, &chanIsCopy);
    JStringReceiver * sr = JStringReceiver::create(env, receiver);
    chuck::RegisterStringReceiver(ch, sr);
}
