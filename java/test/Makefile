.PHONY: all clean

DEPTH=..

CLASSPATH=$(DEPTH):.:junit-4.11.jar:hamcrest-core-1.3.jar

JAVA_SRCS=$(wildcard *.java)
JAVA_CLASSES=$(JAVA_SRCS:.java=.class)

JAVA_OPTIONS="-Djava.library.path=.."

all .DEFAULT: $(JAVA_CLASSES)
	./run $(CLASSPATH) $(JAVA_OPTIONS)

%.class: %.java
	javac -cp $(CLASSPATH) $^

clean:
	-rm *.class *~
