/*
 * libchuck
 * Brian Sorahan 2014
 */
#ifndef __CHUCK_HPP__
#define __CHUCK_HPP__

#include <chuck_def.h>
#include <digiio_rtaudio.h>

namespace chuck {
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
         * start the vm
         */
        virtual t_CKBOOL run() = 0;

    };

    /*
     * Create a new instance of Chuck
     */
    t_CKBOOL
    Create(Chuck ** chuck,
           t_CKUINT port,
           const char * chugins[] = {},
           t_CKUINT nchugins = 0,
           t_CKBOOL enable_audio = TRUE,
           t_CKBOOL vm_halt = TRUE,
           t_CKUINT srate = SAMPLING_RATE_DEFAULT,
           t_CKUINT buffer_size = BUFFER_SIZE_DEFAULT,
           t_CKUINT num_buffers = NUM_BUFFERS_DEFAULT,
           t_CKUINT dac = 0,
           t_CKUINT adc = 0,
           t_CKUINT dac_chans = 2,
           t_CKUINT adc_chans = 2,
           t_CKBOOL block = FALSE,
           t_CKINT  adaptive_size = 0,
           t_CKBOOL force_srate = FALSE);
}

#endif
