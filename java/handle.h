/*
 * This code was graciously lifted from
 * http://thebreakfastpost.com/2012/01/23/wrapping-a-c-library-with-jni-part-1/
 * (and parts 2 and 3)
 */
#ifndef _HANDLE_H_INCLUDED_
#define _HANDLE_H_INCLUDED_

#include <jni.h>

jfieldID getHandleField(JNIEnv *env, jobject obj) {
    jclass c = env->GetObjectClass(obj);
    // J is the type signature for long:
    return env->GetFieldID(c, "nativeHandle", "J");
}

template <typename T>
T * getHandle(JNIEnv *env, jobject obj) {
    jlong handle = env->GetLongField(obj, getHandleField(env, obj));
    return reinterpret_cast<T *>(handle);
}

template <typename T>
void setHandle(JNIEnv *env, jobject obj, T * t) {
    jlong handle = reinterpret_cast<jlong>(t);
    env->SetLongField(obj, getHandleField(env, obj), handle);
}

#endif
