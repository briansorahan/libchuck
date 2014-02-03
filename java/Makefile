#
# libchuck - java bindings Makefile
# Brian Sorahan 2014
#
.PHONY: all test clean

DEPTH=..

CHUCK=Chuck
CHUCK_PKG=edu.princeton.cs.chuck
CHUCK_FQN=$(CHUCK_PKG).$(CHUCK)
CHUCK_JSRC=$(CHUCK).java
CHUCK_CLASS=$(CHUCK).class
CHUCK_SRC=$(CHUCK).cpp
CHUCK_OBJ=$(CHUCK_SRC:.cpp=.o)
CHUCK_H=$(subst .,_,$(CHUCK_FQN)).h
JAVA_SO=libjchuck.so
CHUCK_AR=$(DEPTH)/src/libchuck.a

TEST_DIR=test

CXX=g++
CPPFLAGS := -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux
CFLAGS := -Wl,-Bsymbolic -fPIC -shared
LDFLAGS := -Bsymbolic

all .DEFAULT: $(JAVA_SO)

$(JAVA_SO): $(CHUCK_OBJ) $(CHUCK_AR)
	$(CXX) -shared -L$(DEPTH)/src $(CHUCK_OBJ) \
        -o $(JAVA_SO) \
        -Wl,-Bsymbolic -Wl,--whole-archive $(CHUCK_AR) -Wl,--no-whole-archive \
        -lchuck -lsndfile -lasound -lpthread -ldl -lm

$(CHUCK_AR):
	$(MAKE) -C $(DEPTH)

$(CHUCK_OBJ): $(CHUCK_SRC)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c -o $(CHUCK_OBJ) $(CHUCK_SRC)

$(CHUCK_SRC): $(CHUCK_H)

$(CHUCK_H): $(CHUCK_CLASS)
	javah $(CHUCK_FQN)

$(CHUCK_CLASS):
	javac $(subst .,/,$(CHUCK_FQN)).java

test: $(JAVA_SO)
	$(MAKE) -C test

clean:
	-rm -f $(JAVA_SO) $(CHUCK_H) $(CHUCK_CLASS) *~ *.o
	$(MAKE) -C $(TEST_DIR) clean
