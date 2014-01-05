#include <list>
#include <string>
#include <vector>

// headers from chuck distribution
#include <chuck_compile.h>
#include <chuck_def.h>
#include <chuck_dl.h>
#include <chuck_errmsg.h>
#include <chuck_globals.h>
#include <chuck_vm.h>
#include <digiio_rtaudio.h>
#include <util_string.h>

// libchuck headers
#include "chuck.hpp"

namespace chuck {
    using std::list;
    using std::string;
    using std::vector;

    class ChuckImpl : public Chuck {
    private:
        t_CKUINT m_port;
        Chuck_VM * vm;
        Chuck_Compiler * compiler;
        Chuck_VM_Code * code;
        Chuck_VM_Shred * shred;
        string dac_name; // added 1.3.0.0
        string adc_name; // added 1.3.0.0
        t_CKBOOL dump;
        t_CKBOOL probe;
        t_CKBOOL set_priority;
        t_CKBOOL auto_depend;
        t_CKBOOL enable_shell;
        t_CKBOOL no_vm;
        t_CKBOOL load_hid;
        t_CKBOOL enable_server;
        t_CKBOOL do_watchdog;
        t_CKINT  log_level;
        t_CKINT  deprecate_level; // 1 == warn
        t_CKINT  chugin_load; // 1 == auto (variable added 1.3.0.0)
        t_CKINT priority;
        t_CKBOOL userNamespaceLoaded;

    public:

        ChuckImpl(t_CKUINT port) {
            // global variables
#if defined(__MACOSX_CORE__)
            t_CKINT g_priority = 80;
            // t_CKINT g_priority_low = 60;
#elif defined(__PLATFORM_WIN32__) && !defined(__WINDOWS_PTHREAD__)
            t_CKINT g_priority = THREAD_PRIORITY_HIGHEST;
            // t_CKINT g_priority_low = THREAD_PRIORITY_HIGHEST;
#else
            t_CKINT g_priority = 0x7fffffff;
            // t_CKINT g_priority_low = 0x7fffffff;
#endif

            Chuck_VM::our_priority = g_priority;
            m_port = port;
            compiler = g_compiler = new Chuck_Compiler;
            vm = new Chuck_VM;
            code = NULL;
            shred = NULL;
            dac_name = ""; // added 1.3.0.0
            adc_name = ""; // added 1.3.0.0
            dump = FALSE;
            probe = FALSE;
            set_priority = FALSE;
            auto_depend = FALSE;
            enable_shell = FALSE;
            no_vm = FALSE;
            load_hid = FALSE;
            enable_server = TRUE;
            do_watchdog = TRUE;
            log_level = CK_LOG_CORE;
            deprecate_level = 1; // 1 == warn
            chugin_load = 1; // 1 == auto (variable added 1.3.0.0)
            userNamespaceLoaded = FALSE;
            EM_setlog(log_level);
        }

        t_CKBOOL initializeVM(t_CKBOOL enable_audio,
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
                              t_CKBOOL force_srate) {
            return FALSE != vm->initialize(enable_audio, vm_halt, srate, buffer_size,
                                           num_buffers, dac, adc, dac_chans, adc_chans,
                                           block, adaptive_size, force_srate);
        }

        t_CKBOOL initializeCompiler(const char * chugins[],
                                    t_CKUINT nchugins) {
            t_CKUINT i;
            list<string> dl_search_path;
            string initial_chugin_path;

            if(getenv(g_chugin_path_envvar)) {
                initial_chugin_path = getenv( g_chugin_path_envvar );
            } else {
                initial_chugin_path = g_default_chugin_path;
            }

            parse_path_list(initial_chugin_path, dl_search_path);

            list<string> named_dls;
            for (i = 0; i < nchugins; i++) {
                string dl(chugins[i]);
                named_dls.push_back(dl);
            }

            if (compiler->initialize(vm, dl_search_path, named_dls)) {
                compiler->emitter->dump = dump;
                compiler->set_auto_depend( auto_depend );
                return TRUE;
            } else {
                return FALSE;
            }
        }

        t_CKBOOL initializeSynthesis() {
            return vm->initialize_synthesis();
        }

        t_CKBOOL loadChugins() {
            t_CKBOOL result;
            Chuck_VM_Code * code;
            Chuck_VM_Shred * shred;

            code = NULL;
            shred = NULL;
            result = TRUE;

            // whether or not chug should be enabled (added 1.3.0.0)
            if (chugin_load) {
                // log
                EM_log( CK_LOG_SEVERE, "pre-loading ChucK libs..." );
                EM_pushlog();
        
                // iterate over list of ck files that the compiler found
                list<string>::iterator j;
                for( j = compiler->m_cklibs_to_preload.begin();
                     j != compiler->m_cklibs_to_preload.end();
                     j++) {
                    // the filename
                    string filename = *j;
            
                    // log
                    EM_log( CK_LOG_SEVERE, "preloading '%s'...", filename.c_str() );
                    // push indent
                    EM_pushlog();
            
                    // SPENCERTODO: what to do for full path
                    string full_path = filename;
            
                    // parse, type-check, and emit
                    if(compiler->go( filename, NULL, NULL, full_path )) {
                        // TODO: how to compilation handle?
                        //return 1;

                        // get the code
                        code = compiler->output();
                        // name it - TODO?
                        // code->name += string(argv[i]);

                        // spork it
                        shred = vm->spork( code, NULL );
                    } else {
                        result = FALSE;
                    }
            
                    // pop indent
                    EM_poplog();
                }
        
                // clear the list of chuck files to preload
                compiler->m_cklibs_to_preload.clear();
        
                // pop log
                EM_poplog();
            }

            return result;
        }

        void Destroy() {
            // destruction code here
            delete compiler;
            delete vm;
        }

        t_CKBOOL sporkFile(const char * s) {
            t_CKBOOL result;
            Chuck_VM_Code * code;
            Chuck_VM_Shred * shred;
            vector<string> args;
            string filename;

            code = NULL;
            shred = NULL;
            result = FALSE;

            if (userNamespaceLoaded) {
                compiler->env->load_user_namespace();
            }

            if (! extract_args(s, filename, args)) {
                return FALSE;
            }

            // log
            EM_log( CK_LOG_FINE, "compiling '%s'...", filename.c_str() );
            // push indent
            EM_pushlog();

            // construct full path to be associated with the file so me.sourceDir() works
            // (added 1.3.0.0)
            string full_path = get_full_path(filename);
        
            // parse, type-check, and emit (full_path added 1.3.0.0)
            if(! compiler->go( filename, NULL, NULL, full_path )) {
                return FALSE;
            }

            // get the code
            code = compiler->output();
            // name it
            code->name += string(s);

            // log
            // EM_log( CK_LOG_FINE, "sporking %d %s...", count,
            //         count == 1 ? "instance" : "instances" );

            // spork
            shred = vm->spork( code, NULL );
            // add args
            shred->args = args;

            // pop indent
            EM_poplog();

            return result;
        }
    };

    static Chuck * chuckInstance = NULL;

    t_CKBOOL Create(Chuck ** chuck,
                    t_CKUINT port,
                    const char * chugins[],
                    t_CKUINT nchugins,
                    t_CKBOOL enable_audio,
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
                    t_CKBOOL force_srate) {

        if (chuckInstance == NULL) {
            Chuck * ck = new ChuckImpl(port);
            t_CKBOOL result = TRUE;

            // Initialize the vm
            if (! ck->initializeVM(enable_audio,
                                   vm_halt,
                                   srate,
                                   buffer_size,
                                   num_buffers,
                                   dac,
                                   adc,
                                   dac_chans,
                                   adc_chans,
                                   block,
                                   adaptive_size,
                                   force_srate)) {
                result = FALSE;
            }

            // Initialize the compiler
            if (! ck->initializeCompiler(chugins, nchugins)) {
                result = FALSE;
            }

            *chuck = ck;

            return result;
        }

        *chuck = chuckInstance;
        return true;
    }
}
