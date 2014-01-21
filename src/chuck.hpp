/*
 * libchuck
 * Brian Sorahan 2014
 */
#ifndef CHUCK_HPP
#define CHUCK_HPP

#include <chuck_def.h>
#include <digiio_rtaudio.h>
#include <libchuck_types.h>

namespace chuck {

    typedef struct libchuck_env libchuck_env;

    typedef void (*int_event_cb)(t_CKINT val);
    typedef void (*float_event_cb)(t_CKFLOAT val);
    typedef void (*string_event_cb)(const char * s);

    /*
     * Event receiver types.
     * Receiving a chuck event in C++ is asynchronous, so the user
     * must register callbacks.
     */

    class BaseReceiver {
    public:
        // subscribe to events on a channel
        void ListenTo(const char * channel);
        // run the callback
        virtual void Signal(libchuck_channel_data cd) = 0;
    };

    class IntReceiver : public BaseReceiver {
    public:
        static IntReceiver * New(int_event_cb cb);
    };

    class FloatReceiver : public BaseReceiver {
    public:
        static FloatReceiver * New(float_event_cb cb);
    };

    class StringReceiver : public BaseReceiver {
    public:
        static StringReceiver * New(string_event_cb cb);
    };

    // spork a file
    bool Spork(unsigned int files, const char ** filenames);

    // yield the current process to the chuck vm
    bool Yield();

    // send an int to chuck
    void SendTo(const char * channel, t_CKINT val);
    // send a float to chuck
    void SendTo(const char * channel, t_CKFLOAT val);
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
