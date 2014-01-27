/*
 * libchuck
 * Brian Sorahan 2014
 */
#ifndef CHUCK_HPP
#define CHUCK_HPP

namespace chuck {

    class Chuck {
    public:
        virtual bool Spork(unsigned int files, const char ** filenames) = 0;
        virtual bool Run() = 0;
        virtual void Destroy() = 0;
    };

    class IntReceiver {
    public:
        virtual void receive(long val) = 0;
    };

    class FloatReceiver {
    public:
        virtual void receive(double val) = 0;
    };

    class StringReceiver {
    public:
        virtual void receive(const char * s) = 0;
    };

    bool Create(Chuck ** ck);

    // spork a file
    bool Spork(unsigned int files, const char ** filenames);

    // yield the current process to the chuck vm
    bool Run();

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
