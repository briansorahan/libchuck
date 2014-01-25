.PHONY: all clean

DEPTH=..

CHUCK=Chuck
CHUCK_PKG=edu.princeton.cs.chuck
CHUCK_FQN=$(CHUCK_PKG).$(CHUCK)
CHUCK_JSRC=$(CHUCK).java
CHUCK_CLASS=$(CHUCK).class
CHUCK_SRC=$(CHUCK).cpp
CHUCK_H=$(subst .,_,$(CHUCK_FQN)).h
SO=libjchuck.so

CPPFLAGS := -I$(JAVA_HOME)/include
CFLAGS := -Wl,-Bsymbolic -fPIC -shared

all: $(SO)

$(SO): $(CHUCK_H)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $(SO) $(CHUCK_SRC)

$(CHUCK_H): $(CHUCK_CLASS)
	javah $(CHUCK_FQN)

$(CHUCK_CLASS):
	javac $(subst .,/,$(CHUCK_FQN)).java

clean:
	-rm -f $(SO) $(CHUCK_H) $(CHUCK_CLASS) *~
