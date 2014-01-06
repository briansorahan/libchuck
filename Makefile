.PHONY: libchuck linux-alsa linux-jack \
        clean chuck-clean test-clean gtest-clean all-clean \
        test chuck-test-all chuck-osc-test

# TODO(bsorahan): Support mac and windows
CHUCK_DEFAULT_TARGET=linux-alsa

LIBCHUCK_SRC=src
CHUCK_SRC=chuck/src
# Get the member list for the initial chuck archive
include $(CHUCK_SRC)/vars.mk
CK_OBJS := $(addprefix $(CHUCK_SRC)/, $(CK_OBJS))
CHUCK_BIN=$(CHUCK_SRC)/chuck
LIBCHUCK_ARCHIVE=$(LIBCHUCK_SRC)/libchuck.a

TEST_DIR=test
GTEST_DIR=$(TEST_DIR)/gtest-1.7.0
GTEST_MAKE=$(GTEST_DIR)/make
GTEST_ARCHIVE=$(GTEST_MAKE)/gtest_main.a
LIBCHUCK_TEST=$(TEST_DIR)/libchuck_test
CHUCK_UTIL_STRING_TEST=$(TEST_DIR)/chuck_util_string_test
CHUCK_TESTS=$(TEST_DIR)/ck
CHUCK_OSC_TESTS=$(CHUCK_TESTS)/osc
OSC_TEST_CLASSES := OscTestRunner OscTest
OSC_TEST_CLASSES := $(addprefix $(CHUCK_OSC_TESTS)/classes/, $(OSC_TEST_CLASSES))
OSC_TEST_CLASSES := $(addsuffix .ck, $(OSC_TEST_CLASSES))
OSC_TEST_SCRIPTS=$(wildcard $(CHUCK_OSC_TESTS)/*.ck)

LIBCHUCK_CXXSRCS := src/chuck.cpp
LIBCHUCK_CXXOBJS := $(LIBCHUCK_CXXSRCS:.cpp=.o)
LIBCHUCK_OBJS := $(LIBCHUCK_CXXOBJS)

CXX=g++
CPPFLAGS := -I$(CHUCK_SRC) -I$(LIBCHUCK_SRC) \
            -I$(GTEST_DIR)/include \
            -D__LINUX_ALSA__ -D__PLATFORM_LINUX__ \
            -fno-strict-aliasing -D__CK_SNDFILE_NATIVE__
ifeq ($(MODE),DEBUG)
CXXFLAGS := -std=c++11 -g -Wall -Wextra
CKFLAGS += CHUCK_DEBUG=1
else
CXXFLAGS := -std=c++11 -O3 -Wall -Wextra
endif
LDFLAGS := -L$(LIBCHUCK_SRC)
LDLIBS := $(GTEST_ARCHIVE) -lchuck -lasound -lsndfile \
          -lstdc++ -lpthread -ldl -lm

libchuck .DEFAULT: $(LIBCHUCK_ARCHIVE)

$(LIBCHUCK_ARCHIVE): $(CK_OBJS) $(LIBCHUCK_OBJS)
	ar -rcs $(LIBCHUCK_ARCHIVE) $(LIBCHUCK_OBJS) $(CK_OBJS)

$(CK_OBJS) $(CHUCK_BIN):
	$(MAKE) -C $(CHUCK_SRC) $(CKFLAGS) $(CHUCK_DEFAULT_TARGET)

linux-alsa:
	$(MAKE) -C chuck linux-alsa

linux-jack:
	$(MAKE) -C chuck linux-jack

# Cleaning tasks

clean:
	-rm -f $(LIBCHUCK_OBJS) $(LIBCHUCK_ARCHIVE) $(LIBCHUCK_SRC)/*~ *~

chuck-clean:
	$(MAKE) -C $(CHUCK_SRC) clean

test-clean:
	-rm -f $(LIBCHUCK_TEST) \
           $(CHUCK_UTIL_STRING_TEST)

gtest-clean:
	$(MAKE) -C $(GTEST_MAKE) clean

all-clean: clean chuck-clean test-clean gtest-clean

# Testing tasks

test: $(GTEST_ARCHIVE) $(LIBCHUCK_TEST) \
                       $(CHUCK_UTIL_STRING_TEST)
	$(LIBCHUCK_TEST)
	$(CHUCK_UTIL_STRING_TEST)

chuck-test-all: $(CHUCK_BIN) chuck-osc-test

chuck-osc-test: $(CHUCK_BIN)
	$(CHUCK_BIN) $(OSC_TEST_CLASSES) $(OSC_TEST_SCRIPTS)

$(GTEST_ARCHIVE):
	$(MAKE) -C $(GTEST_MAKE)

retest: test-clean test
