.PHONY: libchuck linux-alsa linux-jack clean chuck-clean test-clean gtest-clean all-clean test

CHUCK_DEFAULT_TARGET_LINUX=linux-alsa

LIBCHUCK_SRC=src
CHUCK_SRC=chuck/src
# NOTE(bsorahan): This name is used for the archive we build from chuck's source,
#                 then libchuck just copies it to a new dir and adds more members.
ARCHIVE_NAME=libchuck.a
CHUCK_ARCHIVE=$(CHUCK_SRC)/$(ARCHIVE_NAME)
LIBCHUCK_ARCHIVE=$(LIBCHUCK_SRC)/$(ARCHIVE_NAME)

TEST_DIR=test
GTEST_DIR=$(TEST_DIR)/gtest-1.7.0
GTEST_MAKE=$(GTEST_DIR)/make
GTEST_ARCHIVE=$(GTEST_MAKE)/gtest_main.a
TEST_PROG=$(TEST_DIR)/libchuck_test

LIBCHUCK_CXXSRCS := src/chuck.cpp
LIBCHUCK_CXXOBJS := $(LIBCHUCK_CXXSRCS:.cpp=.o)
LIBCHUCK_OBJS := $(LIBCHUCK_CXXOBJS)

CXX=g++
CPPFLAGS := -I$(CHUCK_SRC) -I$(LIBCHUCK_SRC) -I$(GTEST_DIR)/include -D__LINUX_ALSA__ -D__PLATFORM_LINUX__ -O3 -fno-strict-aliasing -D__CK_SNDFILE_NATIVE__
CXXFLAGS := -std=c++11 -g -Wall -Wextra
LDFLAGS := -L$(LIBCHUCK_SRC)
LDLIBS := $(GTEST_ARCHIVE) -lchuck -lasound -lsndfile -lstdc++ -lpthread -ldl -lm

libchuck .DEFAULT: $(LIBCHUCK_ARCHIVE)

$(LIBCHUCK_ARCHIVE): $(CHUCK_ARCHIVE) $(LIBCHUCK_OBJS)
	-cp -f $(CHUCK_ARCHIVE) $(LIBCHUCK_ARCHIVE) && \
    ar -rs $(LIBCHUCK_ARCHIVE) $(LIBCHUCK_OBJS)

# TODO(bsorahan): Support for mac and windows
# NOTE(bsorahan): I have modified chuck's makefile to create an archive
$(CHUCK_ARCHIVE):
	$(MAKE) -C $(CHUCK_SRC) $(CHUCK_DEFAULT_TARGET_LINUX)

linux-alsa:
	$(MAKE) -C chuck linux-alsa

linux-jack:
	$(MAKE) -C chuck linux-jack

clean:
	-rm -f $(LIBCHUCK_OBJS) $(LIBCHUCK_ARCHIVE) $(LIBCHUCK_SRC)/*~ *~

chuck-clean:
	$(MAKE) -C $(CHUCK_SRC) clean

test-clean:
	-rm -f $(TEST_PROG)

gtest-clean:
	$(MAKE) -C $(GTEST_MAKE) clean

all-clean: clean chuck-clean test-clean gtest-clean

test: $(GTEST_ARCHIVE) $(TEST_PROG)
	$(TEST_PROG)

$(GTEST_ARCHIVE):
	$(MAKE) -C $(GTEST_MAKE)
