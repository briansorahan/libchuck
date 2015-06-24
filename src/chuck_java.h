/*
 * run chuck with jvm support
 */
#ifndef __INCLUDED_CHUCK_JAVA_H
#define __INCLUDED_CHUCK_JAVA_H

#ifdef HAVE_CONFIG_H
#include "../config.h"
#endif

#if ENABLE_JAVA

#include "chuck.h"

#include <jni.h>
#include <stdio.h>
#include <stdlib.h>

namespace chuck {
    namespace java {
        class ChuckJava : public chuck::Chuck {};

        bool Create(ChuckJava ** jck, JNIEnv * jenv);

        class JIntReceiver : public chuck::IntReceiver {
        public:
            static JIntReceiver * Create(JNIEnv * jenv, jobject obj);
        };

        class JFloatReceiver : public chuck::FloatReceiver {
        public:
            static JFloatReceiver * Create(JNIEnv * jenv, jobject obj);
        };

        class JStringReceiver : public chuck::StringReceiver {
        public:
            static JStringReceiver * Create(JNIEnv * jenv, jobject obj);
        };
    }
}

#endif // ENABLE_JAVA
#endif // __INCLUDED_CHUCK_JAVA_H
