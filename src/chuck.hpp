/*
 * libchuck
 * Brian Sorahan 2014
 */
#ifndef CHUCK_HPP
#define CHUCK_HPP

namespace chuck {

    class Chuck {
    public:
        // spork some files
        virtual bool Spork(unsigned int files, const char ** filenames) = 0;
        // yield the current thread to the chuck vm
        virtual bool Run() = 0;
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
    void RegisterIntReceiver(const char * s, IntReceiver * cb);
    // receive floats from a channel
    void RegisterFloatReceiver(const char * s, FloatReceiver * cb);
    // receive strings from a channel
    void RegisterStringReceiver(const char * s, StringReceiver * cb);

}

#endif // CHUCK_HPP
