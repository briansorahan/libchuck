.PHONY: all clean

DEPTH=..

CLASSPATH=$(DEPTH):.:junit-4.11.jar:hamcrest-core-1.3.jar

TEST_CLASS=JchuckTest
JAVA_SRCS=$(wildcard *.java)
JAVA_CLASSES=$(subst .java,.class,$(JAVA_SRCS))

JAVA_OPTIONS="-Djava.library.path=.."

all .DEFAULT: $(JAVA_CLASSES)
	java -Djava.library.path=.. -cp $(CLASSPATH) org.junit.runner.JUnitCore $(TEST_CLASS)

%.class: %.java
	javac -cp $(CLASSPATH) $^

clean:
	-rm -rf *.class *~
