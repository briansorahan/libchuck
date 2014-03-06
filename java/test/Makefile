.PHONY: all clean

DEPTH=../..

CLASSPATH=$(DEPTH)/java:.:junit-4.11.jar:hamcrest-core-1.3.jar:../libchuck.jar

TEST_CLASS=JchuckTest
JAVA_SRCS=$(wildcard *.java)
JAVA_CLASSES=$(subst .java,.class,$(JAVA_SRCS))

all .DEFAULT: $(JAVA_CLASSES)
	java -Xcheck:jni -cp $(CLASSPATH) org.junit.runner.JUnitCore $(TEST_CLASS)

%.class: %.java
	javac -cp $(CLASSPATH) $^

clean:
	-rm -rf *.class *~

java-bindings:
	make -C .. clean && make -C ..

libchuck:
	cd $(DEPTH) && make && sudo make install
