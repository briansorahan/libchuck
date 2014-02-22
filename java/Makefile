#
# libchuck - java bindings Makefile
# Brian Sorahan 2014
#
.PHONY: all test clean

DEPTH=..
SRC=$(DEPTH)/src
LIBS=$(SRC)/.libs

CHUCK=Jchuck
CHUCK_PKG=edu.princeton.cs.chuck
CHUCK_FQN=$(CHUCK_PKG).$(CHUCK)
CHUCK_JSRC=$(CHUCK).java
CHUCK_CLASS=$(CHUCK).class
CHUCK_SRC=$(CHUCK).cpp
CHUCK_OBJ=$(CHUCK_SRC:.cpp=.o)
CHUCK_LA=$(LIBS)/libchuck.la
CHUCK_H=$(subst .,_,$(CHUCK_FQN)).h
JAVA_DIR=$(subst .,/,$(CHUCK_PKG))
JAVA_SO=libjchuck.so

TEST_DIR=test

CXX=g++
CPPFLAGS := -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -I$(SRC)
ifeq ($(MODE),DEBUG)
	CFLAGS = -fPIC -Wall -g
else
	CFLAGS = -fPIC -Wall -O3
endif
LDFLAGS := -Bsymbolic

all .DEFAULT: $(JAVA_SO)

$(JAVA_SO): $(CHUCK_OBJ) $(CHUCK_LA)
	$(CXX) -pthread -shared -L$(LIBS) $(CHUCK_OBJ) \
        -Wl,-R$(LIBS) -Wl,-R/usr/local/lib \
        -lchuck -lsndfile -lasound -ldl -lm \
        -o $(JAVA_SO)

$(CHUCK_LA):
	cd .. && ./configure && make

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
	-rm -f $(JAVA_SO) $(CHUCK_H) $(JAVA_DIR)/$(CHUCK_CLASS) *~ *.o
	$(MAKE) -C $(TEST_DIR) clean
