#include <assert.h>
#include <jni.h>
#include <stdio.h>

#include "../src/chuck.h"
#include "edu_princeton_cs_chuck_Jchuck.h"

class JChuck {
public:
    JChuck() {
        bool created = chuck::Create(&chuck);
        assert(created);
    }

    virtual ~JChuck() {
        assert(chuck);
        chuck->Destroy();
    }

    bool Spork(unsigned int files, const char ** filenames) {
        return chuck->Spork(files, filenames);
    }

    bool Run() {
        return chuck->Run();
    }

private:
    chuck::Chuck * chuck;
};

// static jchuck instance
static JChuck * jchuck = NULL;

/*
 * Class:     edu_princeton_cs_chuck_Chuck
 * Method:    initialize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_edu_princeton_cs_chuck_Jchuck_initialize(JNIEnv * env, jclass clazz) {
    jchuck = new JChuck();
}

// JNI methods
JNIEXPORT jboolean JNICALL Java_edu_princeton_cs_chuck_Jchuck_spork(JNIEnv * env,
                                                                   jobject thisobj,
                                                                   jobjectArray files) {
    assert(jchuck);

    jsize numfiles = env->GetArrayLength(files);

    // convert files to char **
    const char * filenames[numfiles];

    unsigned int i;
    for (i = 0; i < numfiles; i++) {
        jstring filename = static_cast< jstring >(env->GetObjectArrayElement(files, i));
        if (NULL == filename) return false;

        const char * f = env->GetStringUTFChars(filename, NULL);
        if (NULL == f) return false;

        filenames[i] = f;
    }

    return jchuck->Spork((unsigned int) numfiles, filenames);
}

JNIEXPORT jboolean JNICALL Java_edu_princeton_cs_chuck_Jchuck_run(JNIEnv * env, jobject thisobj) {
    assert(jchuck);
    return jchuck->Run();
}

