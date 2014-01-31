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
CHUCK_H=$(subst .,_,$(CHUCK_FQN)).h
SO=libjchuck.so

TEST_DIR=test

CXX=g++
CPPFLAGS := -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux
CFLAGS := -Wl,-Bsymbolic -fPIC -shared

all .DEFAULT: $(SO)

$(SO): $(CHUCK_H)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -o $(SO) $(CHUCK_SRC)

$(CHUCK_H): $(CHUCK_CLASS)
	javah $(CHUCK_FQN)

$(CHUCK_CLASS):
	javac $(subst .,/,$(CHUCK_FQN)).java

test: $(SO)
	$(MAKE) -C test

clean:
	-rm -f $(SO) $(CHUCK_H) $(CHUCK_CLASS) *~
	$(MAKE) -C $(TEST_DIR) clean
