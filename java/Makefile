.PHONY: all clean

CHUCK=Chuck
CHUCK_JSRC=$(CHUCK).java
CHUCK_CLASS=$(CHUCK).class
CHUCK_SRC=$(CHUCK).c
CHUCK_H=$(CHUCK).h
SO=libchuck.so

CPPFLAGS := -I$(JAVA_HOME)/include
CFLAGS := -Wl,-Bsymbolic -fPIC -shared

all: $(SO)

$(SO): $(CHUCK_H)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $(SO) $(CHUCK_SRC)

$(CHUCK_H): $(CHUCK_CLASS)
	javah $(CHUCK)

$(CHUCK_CLASS):
	javac $(CHUCK_JSRC)

clean:
	-rm -f $(SO) $(CHUCK_H) $(CHUCK_CLASS) *~