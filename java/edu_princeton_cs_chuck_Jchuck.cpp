#include <assert.h>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>

#include "handle.h"
#include "../src/chuck_java.h"
#include "edu_princeton_cs_chuck_Jchuck.h"

using chuck::java::ChuckJava;
using chuck::java::JIntReceiver;
using chuck::java::JFloatReceiver;
using chuck::java::JStringReceiver;

/*
 * Class:     edu_princeton_cs_chuck_Chuck
 * Method:    initialize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_edu_princeton_cs_chuck_Jchuck_initialize(JNIEnv * env, jobject obj) {
    ChuckJava * ckj;
    chuck::java::Create(&ckj, env);
    assert(ckj);
    setHandle(env, obj, ckj);
}

/*
 * Class:     edu_princeton_cs_chuck_Jchuck
 * Method:    spork
 * Signature: ([Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_edu_princeton_cs_chuck_Jchuck_spork(JNIEnv * env,
                                                                   jobject obj,
                                                                   jobjectArray files) {
    ChuckJava * ckj = getHandle< ChuckJava >(env, obj);
    assert(ckj);

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

    return ckj->Spork((unsigned int) numfiles, filenames);
}

/*
 * Class:     edu_princeton_cs_chuck_Jchuck
 * Method:    run
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_edu_princeton_cs_chuck_Jchuck_run(JNIEnv * env, jobject obj) {
    ChuckJava * ckj = getHandle< ChuckJava >(env, obj);
    assert(ckj);
    return ckj->Wait();
}

/*
 * send/receive methods
 */

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
Java_edu_princeton_cs_chuck_Jchuck_receiveFrom__Ljava_lang_String_2Ledu_princeton_cs_chuck_IntReceiver_2(JNIEnv * env, jobject obj, jstring chan, jobject receiver) {
    jboolean chanIsCopy;
    const char * ch = env->GetStringUTFChars(chan, &chanIsCopy);
    JIntReceiver * ir = JIntReceiver::Create(env, receiver);
    chuck::RegisterIntReceiver(ch, ir);
}

/*
 * Class:     edu_princeton_cs_chuck_Jchuck
 * Method:    receiveFrom
 * Signature: (Ljava/lang/String;Ledu/princeton/cs/chuck/Jchuck/FloatReceiver;)V
 */
JNIEXPORT void JNICALL
Java_edu_princeton_cs_chuck_Jchuck_receiveFrom__Ljava_lang_String_2Ledu_princeton_cs_chuck_FloatReceiver_2(JNIEnv * env, jobject obj, jstring chan, jobject receiver) {
    jboolean chanIsCopy;
    const char * ch = env->GetStringUTFChars(chan, &chanIsCopy);
    JFloatReceiver * fr = JFloatReceiver::Create(env, receiver);
    chuck::RegisterFloatReceiver(ch, fr);
}

/*
 * Class:     edu_princeton_cs_chuck_Jchuck
 * Method:    receiveFrom
 * Signature: (Ljava/lang/String;Ledu/princeton/cs/chuck/Jchuck/StringReceiver;)V
 */
JNIEXPORT void JNICALL
Java_edu_princeton_cs_chuck_Jchuck_receiveFrom__Ljava_lang_String_2Ledu_princeton_cs_chuck_StringReceiver_2(JNIEnv * env, jobject obj, jstring chan, jobject receiver) {
    jboolean chanIsCopy;
    const char * ch = env->GetStringUTFChars(chan, &chanIsCopy);
    JStringReceiver * sr = JStringReceiver::Create(env, receiver);
    chuck::RegisterStringReceiver(ch, sr);
}
