.PHONY: all clean

CHUCK_SRC=../chuck/src
LIBCHUCK_SRC=../src
GTEST_DIR=gtest-1.7.0
GTEST_MAKE=$(GTEST_DIR)/make
GTEST_AR=$(GTEST_MAKE)/gtest_main.a
LIBCHUCK_TEST=libchuck_test
LIBCHUCK_TEST_SRC=$(LIBCHUCK_TEST).cpp
CHUCK_UTIL_STRING_TEST=chuck_util_string_test
CHUCK_TESTS=ck
CHUCK_OSC_TESTS=$(CHUCK_TESTS)/osc
OSC_TEST_CLASSES := OscTestRunner OscTest
OSC_TEST_CLASSES := $(addprefix $(CHUCK_OSC_TESTS)/classes/, $(OSC_TEST_CLASSES))
OSC_TEST_CLASSES := $(addsuffix .ck, $(OSC_TEST_CLASSES))
OSC_TEST_SCRIPTS=$(wildcard $(CHUCK_OSC_TESTS)/*.ck)

CXX=g++
CPPFLAGS := -I$(CHUCK_SRC) -I$(LIBCHUCK_SRC) -I$(GTEST_DIR)/include

ifeq ($(MODE),DEBUG)
CXXFLAGS := -std=c++11 -g -Wall -Wextra
else
CXXFLAGS := -std=c++11 -O3 -Wall -Wextra
endif

# linker flags
LDFLAGS := -L$(LIBCHUCK_SRC)
LDLIBS := $(GTEST_AR) -lchuck -lasound -lsndfile -lpthread -lstdc++ -ldl -lm

TESTS := $(LIBCHUCK_TEST) \
         $(CHUCK_UTIL_STRING_TEST)

all: $(TESTS) $(GTEST_AR)
	./$(LIBCHUCK_TEST)
	./$(CHUCK_UTIL_STRING_TEST)

$(GTEST_AR):
	$(MAKE) -C $(GTEST_DIR)/make

$(TESTS): $(GTEST_AR)

clean:
	-rm -f $(TESTS) *.o *~

gtest-clean:
	$(MAKE) -C $(GTEST_DIR)/make
