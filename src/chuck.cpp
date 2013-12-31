#include <list>
#include <string>
#include <vector>

#include <chuck_compile.h>
#include <chuck_def.h>
#include <chuck_errmsg.h>
#include <chuck_vm.h>
#include <digiio_rtaudio.h>

#include "chuck.hpp"

namespace chuck {
    using std::list;
    using std::string;
    using std::vector;

    class ChuckImpl : public Chuck {
    private:

        // ==========================================
        // Begin chuck_main.cpp variable declarations
        // ==========================================

        Chuck_Compiler * compiler;
        Chuck_VM * vm;
        Chuck_VM_Code * code;
        Chuck_VM_Shred * shred;
        t_CKBOOL enable_audio;
        t_CKBOOL vm_halt;
        t_CKUINT srate;
        t_CKBOOL force_srate; // added 1.3.1.2
        t_CKUINT buffer_size;
        t_CKUINT num_buffers;
        t_CKUINT dac;
        t_CKUINT adc;
        string dac_name; // added 1.3.0.0
        string adc_name; // added 1.3.0.0
        t_CKUINT dac_chans;
        t_CKUINT adc_chans;
        t_CKBOOL dump;
        t_CKBOOL probe;
        t_CKBOOL set_priority;
        t_CKBOOL auto_depend;
        t_CKBOOL block;
        t_CKBOOL enable_shell;
        t_CKBOOL no_vm;
        t_CKBOOL load_hid;
        t_CKBOOL enable_server;
        t_CKBOOL do_watchdog;
        t_CKINT  adaptive_size;
        t_CKINT  log_level;
        t_CKINT  deprecate_level; // 1 == warn
        t_CKINT  chugin_load; // 1 == auto (variable added 1.3.0.0)
        string   filename;
        vector<string> args;
        // list of search pathes (added 1.3.0.0)
        list<string> dl_search_path;
        // initial chug-in path (added 1.3.0.0)
        string initial_chugin_path;
        // list of individually named chug-ins (added 1.3.0.0)
        list<string> named_dls;

        t_CKUINT files;
        t_CKUINT count;
        t_CKINT i;

        // ========================================
        // End chuck_main.cpp variable declarations
        // ========================================

        t_CKINT priority;
        int m_port;

    public:

        ChuckImpl(int port) {
            m_port = port;
            Chuck_Compiler * compiler = NULL;
            Chuck_VM * vm = NULL;
            Chuck_VM_Code * code = NULL;
            Chuck_VM_Shred * shred = NULL;
            t_CKBOOL enable_audio = TRUE;
            t_CKBOOL vm_halt = TRUE;
            t_CKUINT srate = SAMPLING_RATE_DEFAULT;
            t_CKBOOL force_srate = FALSE; // added 1.3.1.2
            t_CKUINT buffer_size = BUFFER_SIZE_DEFAULT;
            t_CKUINT num_buffers = NUM_BUFFERS_DEFAULT;
            t_CKUINT dac = 0;
            t_CKUINT adc = 0;
            string dac_name = ""; // added 1.3.0.0
            string adc_name = ""; // added 1.3.0.0
            t_CKUINT dac_chans = 2;
            t_CKUINT adc_chans = 2;
            t_CKBOOL dump = FALSE;
            t_CKBOOL probe = FALSE;
            t_CKBOOL set_priority = FALSE;
            t_CKBOOL auto_depend = FALSE;
            t_CKBOOL block = FALSE;
            t_CKBOOL enable_shell = FALSE;
            t_CKBOOL no_vm = FALSE;
            t_CKBOOL load_hid = FALSE;
            t_CKBOOL enable_server = TRUE;
            t_CKBOOL do_watchdog = TRUE;
            t_CKINT  adaptive_size = 0;
            t_CKINT  log_level = CK_LOG_CORE;
            t_CKINT  deprecate_level = 1; // 1 == warn
            t_CKINT  chugin_load = 1; // 1 == auto (variable added 1.3.0.0)
            string   filename = "";
            vector<string> args;
            // list of search pathes (added 1.3.0.0)
            list<string> dl_search_path;
            // initial chug-in path (added 1.3.0.0)
            string initial_chugin_path;
            // list of individually named chug-ins (added 1.3.0.0)
            list<string> named_dls;

            t_CKUINT files = 0;
            t_CKUINT count = 1;
            t_CKINT i;
        }

        void Destroy() {
            // destruction code here
        }

        bool sporkFile(const char ** args) {
            return true;
        }
    };

    Chuck * Create(int port) {
        return new ChuckImpl(port);
    }
}
