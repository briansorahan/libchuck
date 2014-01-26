.PHONY: libchuck \
        clean chuck-clean test-clean gtest-clean all-clean \
        test chuck-test-all chuck-osc-test

# TODO: Support mac and windows

SOLIB_PREFIX=lib
SOLIB_EXT=so
CHUCK_DEFAULT_TARGET=linux-alsa

LIBCHUCK_SRC=src
CHUCK_SRC=chuck/src

# Get the list of chuck objs
-include $(CHUCK_SRC)/vars.mk
LIBCHUCK_CXXSRCS := Chuck.cpp
LIBCHUCK_CXXSRCS := $(addprefix $(LIBCHUCK_SRC),$(LIBCHUCK_CXXSRCS))
LIBCHUCK_OBJS := $(subst .cpp,.o,$(LIBCHUCK_CXXSRCS))

CK_OBJS := $(addprefix $(CHUCK_SRC)/, $(CK_OBJS))
CHUCK_BIN=$(CHUCK_SRC)/chuck
LIBCHUCK_ARCHIVE=$(LIBCHUCK_SRC)/libchuck.a
LIBCHUCK_EXTENSIONS := util_events.o \
                       ulib_events.o

# test
TEST_DIR=test

LIBCHUCK_CXXSRCS := chuck.cpp
LIBCHUCK_CXXSRCS := $(addprefix src/, $(LIBCHUCK_CXXSRCS))
LIBCHUCK_CXXOBJS := $(LIBCHUCK_CXXSRCS:.cpp=.o)
LIBCHUCK_OBJS := $(LIBCHUCK_CXXOBJS)

CXX=g++
CPPFLAGS := -I$(CHUCK_SRC) -I$(LIBCHUCK_SRC) \
            -D__LINUX_ALSA__ -D__PLATFORM_LINUX__ \
            -fno-strict-aliasing -D__CK_SNDFILE_NATIVE__

# compiler flags
ifeq ($(MODE),DEBUG)
CXXFLAGS := -std=c++11 -g -Wall -Wextra -shared -fPIC
CKFLAGS += CHUCK_DEBUG=1
else
CXXFLAGS := -std=c++11 -O3 -Wall -Wextra -shared -fPIC
endif

# linker flags
LDFLAGS := -L$(LIBCHUCK_SRC) -shared -Wl,-Bsymbolic
LDLIBS := -lchuck -lasound -lsndfile -lstdc++ -lpthread -ldl -lm

JAVA_DIR=java

libchuck .DEFAULT: $(LIBCHUCK_ARCHIVE)

$(LIBCHUCK_ARCHIVE): $(CK_OBJS) $(LIBCHUCK_OBJS)
	ar -rcs $(LIBCHUCK_ARCHIVE) $(LIBCHUCK_OBJS) $(CK_OBJS)

$(CK_OBJS) $(CHUCK_BIN):
	$(MAKE) $(CKFLAGS) -C $(CHUCK_SRC) $(CHUCK_DEFAULT_TARGET)

find-jvm:

java-bindings:
	$(MAKE) -C $(JAVA_DIR)

test:
	$(MAKE) -C test

clean:
	-rm -f $(LIBCHUCK_OBJS) $(LIBCHUCK_ARCHIVE) \
           $(LIBCHUCK_SRC)/*~ $(CHUCK_SRC)/*~ *~ \
           $(addprefix $(CHUCK_SRC)/, $(LIBCHUCK_EXTENSIONS)) \
           $(LIBCHUCK_SHARED)

chuck-clean:
	$(MAKE) -C $(CHUCK_SRC) clean

java-clean:
	$(MAKE) -C $(JAVA_DIR) clean

test-clean:
	$(MAKE) -C $(TEST_DIR) clean

all-clean: clean chuck-clean test-clean gtest-clean \
           java-clean
