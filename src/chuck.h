/*
 * libchuck
 * Brian Sorahan 2014
 */
#ifndef _CHUCK_H_INCLUDED
#define _CHUCK_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "../config.h"
#endif

#if ENABLE_JAVA
#include <jni.h>
#endif

namespace chuck {

    class Chuck {
    public:
        // spork a single file
        virtual bool SporkFile(const char * s) = 0;
        // spork some files and run the chuck vm
        virtual bool Spork(unsigned int files, const char ** filenames) = 0;
        // run the chuck vm
        virtual bool RunVM() = 0;
        // wait for the chuck vm thread to finish
        virtual bool Wait() = 0;
        // kill the chuck vm and compiler
        virtual void Destroy() = 0;
    };

    // receive ints from chuck
    class IntReceiver {
    public:
        virtual void receive(long val) = 0;
    };

    // receive floats from chuck
    class FloatReceiver {
    public:
        virtual void receive(double val) = 0;
    };

    // receive strings from chuck
    class StringReceiver {
    public:
        virtual void receive(const char * s) = 0;
    };

    // instantiate the chuck vm and compiler,
    // and initialize the synthesis subsystem
    bool Create(Chuck ** ck);

    // send an int to chuck
    void SendTo(const char * channel, long val);
    // send a float to chuck
    void SendTo(const char * channel, double val);
    // send a string to chuck
    void SendTo(const char * channel, const char * val);

    // receive ints from a channel
    void RegisterIntReceiver(const char * s, IntReceiver * rec);
    // receive floats from a channel
    void RegisterFloatReceiver(const char * s, FloatReceiver * rec);
    // receive strings from a channel
    void RegisterStringReceiver(const char * s, StringReceiver * rec);

    class VMThread {
    public:
        // spawns thread
        virtual void Run(Chuck * ck) = 0;
        // wait for chuck
        virtual bool Wait() = 0;
    };

}

#endif // _CHUCK_H_INCLUDED
