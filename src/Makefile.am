lib_LTLIBRARIES = libchuck.la

libchuck_la_SOURCES = util_console.h \
                hidio_sdl.h \
                chuck_scan.h \
                regex/tre-ast.h \
                regex/tre-mem.h \
                regex/tre-config.h \
                regex/tre-internal.h \
                regex/config.h \
                regex/tre-parse.h \
                regex/xmalloc.h \
                regex/tre-stack.h \
                regex/tre-filter.h \
                regex/tre-match-utils.h \
                regex/tre.h \
                regex/tre-compile.h \
                regex/regex.h \
                util_raw.h \
                util_sndfile.h \
                chuck_vm.h \
                util_hid.h \
                rtmidi.h \
                lo/lo_errors.h \
                lo/lo_lowlevel.h \
                lo/lo_types_internal.h \
                lo/lo_osc_types.h \
                lo/lo_endian.h \
                lo/config.h \
                lo/lo_macros.h \
                lo/lo_types.h \
                lo/lo_internal.h \
                lo/lo.h \
                lo/lo_throw.h \
                chuck_oo.h \
                ulib_std.h \
                chuck_otf.h \
                chuck_instr.h \
                midiio_rtmidi.h \
                chuck_compile.h \
                chuck_ugen.h \
                util_network.h \
                chuck_type.h \
                util_events.h \
                chuck_absyn.h \
                ugen_stk.h \
                dirent_win32.h \
                ugen_xxx.h \
                util_string.h \
                chuck_dl.h \
                uana_extract.h \
                util_opsc.h \
                chuck_stats.h \
                ulib_regex.h \
                ulib_events.h \
                chuck_symbol.h \
                chuck_parse.h \
                chuck_shell.h \
                ugen_filter.h \
                RtAudio/RtError.h \
                RtAudio/original/RtError.h \
                RtAudio/original/RtAudio.h \
                RtAudio/RtAudio.h \
                momu/mo_def.h \
                momu/mo_audio.h \
                util_thread.h \
                util_xforms.h \
                chuck_def.h \
                ulib_opsc.h \
                chuck_lang.h \
                util_serial.h \
                ulib_machine.h \
                uana_xform.h \
                chuck_errmsg.h \
                chuck_frame.h \
                chuck_utils.h \
                ugen_osc.h \
                chuck_bbq.h \
                chuck_console.h \
                chuck_table.h \
                digiio_rtaudio.h \
                chuck_globals.h \
                chuck_win32.h \
                util_math.h \
                chuck_emit.h \
                util_buffers.h \
                ulib_math.h \
                chuck_io.h \
                chuck.tab.c chuck.yy.c util_math.c util_network.c util_raw.c util_xforms.c \
                chuck_absyn.cpp chuck_parse.cpp chuck_errmsg.cpp \
                chuck_frame.cpp chuck_symbol.cpp chuck_table.cpp chuck_utils.cpp \
                chuck_vm.cpp chuck_instr.cpp chuck_scan.cpp chuck_type.cpp chuck_emit.cpp \
                chuck_compile.cpp chuck_dl.cpp chuck_oo.cpp chuck_lang.cpp chuck_ugen.cpp \
                chuck_main.cpp chuck_otf.cpp chuck_stats.cpp chuck_bbq.cpp chuck_shell.cpp \
                chuck_console.cpp chuck_globals.cpp chuck_io.cpp \
                digiio_rtaudio.cpp hidio_sdl.cpp \
                midiio_rtmidi.cpp RtAudio/RtAudio.cpp rtmidi.cpp ugen_osc.cpp ugen_filter.cpp \
                ugen_stk.cpp ugen_xxx.cpp ulib_machine.cpp ulib_math.cpp ulib_std.cpp \
                ulib_opsc.cpp ulib_regex.cpp util_buffers.cpp util_console.cpp \
                util_string.cpp util_thread.cpp util_opsc.cpp util_serial.cpp \
                util_hid.cpp uana_xform.cpp uana_extract.cpp \
                util_events.cpp ulib_events.cpp \
                lo/address.c lo/blob.c lo/bundle.c lo/message.c lo/method.c \
                lo/pattern_match.c lo/send.c lo/server.c lo/server_thread.c lo/timetag.c \
                chuck.cpp # edu_princeton_cs_chuck_jchuck.h jchuck.cpp

libchuck_la_CPPFLAGS = -I$(JAVA_HOME)/include

libchuck_la_LIBADD = -lasound -lsndfile -lm -lpthread -ldl

libchuck_la_LDFLAGS = -release @PACKAGE_VERSION@ -version-info 0:0:0

include_HEADERS = chuck.h

chuck.tab.c chuck.tab.h: chuck.y
	$(YACC) -dv -b chuck chuck.y

chuck.yy.c: chuck.lex
	$(LEX) -ochuck.yy.c chuck.lex

chuck_win32.c: chuck.yy.c
	$(LEX) --nounistd -ochuck.yy.c chuck.lex
	cat chuck.tab.c chuck.yy.c > $@

chuck_win32.h: chuck.tab.h
	cat chuck.tab.h > $@
