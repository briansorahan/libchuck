#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libchuck], [0.0.1], [bsorahan@gmail.com])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([src/chuck.cpp])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_AUX_DIR([ac-config])

AM_INIT_AUTOMAKE([])

AC_CANONICAL_HOST([])

# parameters for aclocal
AC_SUBST(ACLOCAL_AMFLAGS, "-I m4")

# Checks for programs.
AC_PROG_YACC
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LEX
AC_PROG_MAKE_SET

AM_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_FUNC_ALLOCA
AC_CHECK_HEADERS([arpa/inet.h fcntl.h float.h inttypes.h libintl.h limits.h mach/mach.h malloc.h memory.h netdb.h netinet/in.h stddef.h stdint.h stdlib.h string.h sys/ioctl.h sys/param.h sys/socket.h sys/time.h sys/timeb.h termio.h termios.h unistd.h wchar.h wctype.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_UID_T
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_CHECK_MEMBERS([struct stat.st_rdev])
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

#
# Java
#
AC_ARG_ENABLE(java,
  [  --enable-java           Enable java bindings],
  [want_java=$enableval],
  [want_java=no])

#
# TODO: check for java system libraries and headers
#
if test "x$want_java" = "xyes"; then
   AC_DEFINE(ENABLE_JAVA, 1, [Define this to enable java])
fi

#
# cribbed from liblo [bps]
#
# Since we don't require C99, format code for long long int can vary
# in some compilers.  (In particular, MingW seems to require "I64"
# instead of "ll")
#
AC_MSG_CHECKING([how to print long long int])
AC_COMPILE_IFELSE(
  [AC_LANG_PROGRAM([#include <stdio.h>],[printf("%lld", (long long int)0);])],
    [printf_ll=\"ll\"],
    [AC_COMPILE_IFELSE(
      [AC_LANG_PROGRAM([#include <stdio.h>],[printf("%I64d", (long long int)0);])],
        [printf_ll=\"I64\"],
        [AC_MSG_ERROR([printf doesn't support long long int])])])
AC_MSG_RESULT([$printf_ll])
AC_DEFINE_UNQUOTED([PRINTF_LL],[$printf_ll],[printf code for type long long int])

#
# cribbed from liblo [bps]
#
# Check if threads are wanted
AC_ARG_ENABLE(threads,
  [  --enable-threads        Enable server threads (liblo)],
  [want_threads=$enableval],
  [want_threads=yes])


# Check for whether threads are wanted, and if so, did we find libpthread.
if test "x$want_threads" = "xyes"; then
  AC_SEARCH_LIBS([pthread_create], [c pthread],
    [AS_IF([! test "$ac_res" = "-lc" && ! test "$ac_res" = "none required"],
           [LIBPTHREAD="$ac_res"])
     have_threads=yes;
     AC_DEFINE(ENABLE_THREADS, 1, [Define this to enable threads.])],
    [AC_MSG_ERROR(pthread not found. Try option --disable-threads.)])
fi


# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_STRTOD
AC_CHECK_FUNCS([atexit bzero floor ftruncate getcwd gethostbyname gethostname gettimeofday memchr memset pow realpath regcomp select setenv socket sqrt strchr strdup strerror strpbrk strrchr strstr strtol strtoul])

case $host in
	*linux*)
		AC_DEFINE([__PLATFORM_LINUX__],1,[Building for linux platform])
        AC_DEFINE([__LINUX_ALSA__],1,[Use alsa to connect to dac])
        AC_DEFINE([__CK_SNDFILE_NATIVE__],1,[Not sure what this one is for])
		;;
	*win*|mingw)
		AC_DEFINE([__PLATFORM_WIN32__],1,[Building for windows])
		;;
	*mac*)
		AC_DEFINE([__PLATFORM_MACOSX__],1,[Building for mac osx])
		;;
	*)
		;;
esac

AC_CONFIG_FILES([src/Makefile Makefile])
AC_OUTPUT
