
CK_VERSION=1.3.3.0

CK_CSRCS = chuck.tab.c chuck.yy.c util_math.c util_network.c util_raw.c \
	util_xforms.c
CK_CXXSRCS = chuck_absyn.cpp chuck_parse.cpp chuck_errmsg.cpp \
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
    util_events.cpp ulib_events.cpp
CK_LO_CSRCS = lo/address.c lo/blob.c lo/bundle.c lo/message.c lo/method.c \
    lo/pattern_match.c lo/send.c lo/server.c lo/server_thread.c lo/timetag.c

CK_COBJS=$(CK_CSRCS:.c=.o)
CK_CXXOBJS=$(CK_CXXSRCS:.cpp=.o)
CK_LO_COBJS=$(CK_LO_CSRCS:.c=.o)
CK_OBJS=$(CK_COBJS) $(CK_CXXOBJS) $(CK_LO_COBJS)

