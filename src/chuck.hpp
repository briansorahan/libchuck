/*
 * libchuck
 * Brian Sorahan 2014
 */
#ifndef CHUCK_HPP
#define CHUCK_HPP

#include <chuck_def.h>
#include <digiio_rtaudio.h>
#include <libchuck_types.h>


typedef void (*int_event_cb)(t_CKINT val);
typedef void (*float_event_cb)(t_CKFLOAT val);
typedef void (*string_event_cb)(const char * s);

namespace chuck {
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

    class Chuck {
    public:

        virtual void Destroy() = 0;

        virtual t_CKBOOL
        initializeVM(t_CKBOOL enable_audio,
                     t_CKBOOL vm_halt,
                     t_CKUINT srate,
                     t_CKUINT buffer_size,
                     t_CKUINT num_buffers,
                     t_CKUINT dac,
                     t_CKUINT adc,
                     t_CKUINT dac_chans,
                     t_CKUINT adc_chans,
                     t_CKBOOL block,
                     t_CKINT  adaptive_size,
                     t_CKBOOL force_srate) = 0;

        virtual t_CKBOOL
        initializeCompiler(const char * chugins[],
                           t_CKUINT nchugins) = 0;

        virtual t_CKBOOL initializeSynthesis() = 0;

        virtual t_CKBOOL loadChugins() = 0;

        /*
         * Spork a shred from a string.
         * string must be formatted as filename:arg1:arg2:...
         * Returns true/false if the operation succeeds/fails.
         */
        virtual t_CKBOOL sporkFile(const char * s) = 0;

        /*
         * Start the vm as its own process.
         * Return the PID of the new vm.
         */
        virtual t_CKBOOL run() = 0;

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

    void RegisterIntReceiver(int_event_cb cb);
    void RegisterFloatReceiver(float_event_cb cb);
    void RegisterStringReceiver(string_event_cb cb);

}

#endif // CHUCK_HPP
