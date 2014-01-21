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

    class Channel {
    public:
        static const Channel & channel(const char * s);
        bool IsInt() const;
        bool IsFloat() const;
        bool IsString() const;
    private:
        Channel(const char * s);
    };

    typedef void (*int_event_cb)(long val);
    typedef void (*float_event_cb)(double val);
    typedef void (*string_event_cb)(const char * s);

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
    void RegisterIntReceiver(int_event_cb cb);
    // receive floats from a channel
    void RegisterFloatReceiver(float_event_cb cb);
    // receive strings from a channel
    void RegisterStringReceiver(string_event_cb cb);

}

#endif // CHUCK_HPP
