#
# libchuck - java bindings Makefile
# Brian Sorahan 2014
#
.PHONY: all test clean

DEPTH = ..
SRC = $(DEPTH)/src
LIBS = $(SRC)/.libs

JCHUCK_PKG := edu.princeton.cs.chuck
JCHUCK_PKG_DIR := $(subst .,/,$(JCHUCK_PKG))
# JCHUCK_CLASSES := Jchuck IntReceiver FloatReceiver StringReceiver
JCHUCK_CLASSES := Jchuck
JCHUCK_CLASSES := $(addprefix $(JCHUCK_PKG).,$(JCHUCK_CLASSES))
JCHUCK_JAVA_SRCS := $(addsuffix .java,$(subst .,/,$(JCHUCK_CLASSES)))
JCHUCK_HEADERS := $(subst .java,.h,$(subst /,_,$(JCHUCK_JAVA_SRCS)))
JCHUCK_CXX_SRCS := $(subst .java,.cpp,$(subst /,_,$(JCHUCK_JAVA_SRCS)))
JCHUCK_OBJS := $(subst .cpp,.o,$(JCHUCK_CXX_SRCS))
JCHUCK_CLASS_FILES := $(subst .,/,$(JCHUCK_CLASSES))
JCHUCK_CLASS_FILES := $(addsuffix .class,$(JCHUCK_CLASS_FILES))
JCHUCK_CLASSES := $(addsuffix .class,$(JCHUCK_CLASSES))

CHUCK_LA = $(LIBS)/libchuck.la
JAVA_SO = libjchuck.so

TEST_DIR=test

CXX=g++
CPPFLAGS := -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -I$(SRC)
ifeq ($(MODE),DEBUG)
	CFLAGS = -fPIC -Wall -g
else
	CFLAGS = -fPIC -Wall -O3
endif
LDFLAGS := -Bsymbolic

# Don't remove class files
.SECONDARY: $(JCHUCK_CLASS_FILES)

all .DEFAULT: $(JAVA_SO)

$(JAVA_SO): $(JCHUCK_OBJS) $(CHUCK_LA)
	$(CXX) -pthread -shared -L$(LIBS) $(JCHUCK_OBJS) \
        -Wl,-R$(LIBS) -Wl,-R/usr/local/lib \
        -lchuck -lsndfile -lasound -ldl -lm \
        -o $(JAVA_SO)

$(CHUCK_LA):
	cd .. && ./configure && make

$(JCHUCK_OBJS): $(JCHUCK_HEADERS) $(JCHUCK_CXX_SRCS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

edu_princeton_cs_chuck_%.h: edu/princeton/cs/chuck/%.class
	javah $(JCHUCK_PKG).$*

%.class: %.java
	javac $<

test: $(JAVA_SO)
	$(MAKE) -C test

clean:
	-rm -f $(JAVA_SO) $(JCHUCK_HEADERS) $(JCHUCK_PKG_DIR)/*.class *~ *.o
	$(MAKE) -C $(TEST_DIR) clean
