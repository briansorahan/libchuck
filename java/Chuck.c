#include <jni.h>
#include <stdio.h>

#include "Chuck.h"

JNIEXPORT jint JNICALL Java_Chuck_JNIVersion(JNIEnv * env, jobject obj) {
    return (*env)->GetVersion(env);
}

