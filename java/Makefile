#
# libchuck - java bindings Makefile
# Brian Sorahan 2014
#
.PHONY: all test distclean clean chuck-processing

DEPTH = ..
SRC = $(DEPTH)/src
LIBS = $(SRC)/.libs
BUILD_DIR=build
PROCESSING_LIBRARY=chuck/library
# TODO: support mac and windows
LIBCHUCK_PLATFORM=$(shell uname | tr '[:upper:]' '[:lower:]')
LIBCHUCK_ARCH=$(shell $(CC) -dumpmachine | sed -e 's,-.*,,' -e 's,i[3456]86,x86,' -e 's,amd64,x86_64,')
LIBCHUCK_JAR := libchuck.jar
JCHUCK_PKG := edu.princeton.cs.chuck
JCHUCK_PKG_DIR := $(subst .,/,$(JCHUCK_PKG))
BUILD_PKG_DIR=$(BUILD_DIR)/$(JCHUCK_PKG_DIR)
JAR_NATIVES_DIR=$(BUILD_PKG_DIR)/natives/$(LIBCHUCK_PLATFORM)/$(LIBCHUCK_ARCH)

JCHUCK_CLASSES := Jchuck
JCHUCK_CLASSES := $(addprefix $(JCHUCK_PKG).,$(JCHUCK_CLASSES))
JCHUCK_JAVA_SRCS := $(addsuffix .java,$(subst .,/,$(JCHUCK_CLASSES)))
JCHUCK_HEADERS := $(subst .java,.h,$(subst /,_,$(JCHUCK_JAVA_SRCS)))
JCHUCK_CXX_SRCS := $(subst .java,.cpp,$(subst /,_,$(JCHUCK_JAVA_SRCS)))
JCHUCK_OBJS := $(subst .cpp,.o,$(JCHUCK_CXX_SRCS))
JCHUCK_CLASS_FILES := $(subst .,/,$(JCHUCK_CLASSES))
JCHUCK_CLASS_FILES := $(addsuffix .class,$(JCHUCK_CLASS_FILES))
JCHUCK_CLASSES := $(addsuffix .class,$(JCHUCK_CLASSES))
JCHUCK_JAR_CLASSES := Jchuck IntReceiver FloatReceiver StringReceiver NativeLoader
JCHUCK_JAR_CLASSES := $(addprefix $(JCHUCK_PKG_DIR),$(JCHUCK_JAR_CLASSES))

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

all .DEFAULT: $(JAVA_SO) $(LIBCHUCK_JAR)

$(JAVA_SO): $(JCHUCK_OBJS) $(CHUCK_LA)
	$(CXX) -pthread -shared -L$(LIBS) $(JCHUCK_OBJS) \
        -Wl,-R$(LIBS) -Wl,-R/usr/local/lib \
        -lchuck -lsndfile -lasound -ldl -lm \
        -o $(JAVA_SO)

$(LIBCHUCK_JAR): $(JAVA_SO) $(LIBCHUCK_JAR_CLASSES) $(BUILD_DIR)
	cp -R edu $(BUILD_DIR)
	mkdir -p $(JAR_NATIVES_DIR)
	cp $(JAVA_SO) $(JAR_NATIVES_DIR)
	jar -cvf $(LIBCHUCK_JAR) -C $(BUILD_DIR) edu/princeton/cs/chuck

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(CHUCK_LA):
	cd .. && ./configure && make

$(JCHUCK_OBJS): $(JCHUCK_HEADERS) $(JCHUCK_CXX_SRCS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

edu_princeton_cs_chuck_%.h: edu/princeton/cs/chuck/%.class
	javah $(JCHUCK_PKG).$*

%.class: %.java
	javac $<

processing-library: $(LIBCHUCK_JAR)
	cp $(LIBCHUCK_JAR) $(PROCESSING_LIBRARY)

test: $(JAVA_SO)
	$(MAKE) -C test

distclean clean:
	-rm -rf $(JAVA_SO) $(JCHUCK_HEADERS) $(JCHUCK_PKG_DIR)/*.class \
            $(LIBCHUCK_JAR) *~ *.o *.class $(BUILD_DIR) \
            $(PROCESSING_LIBRARY)/$(LIBCHUCK_JAR)
	$(MAKE) -C $(TEST_DIR) clean
