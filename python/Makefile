.PHONY: all clean install test

TEST_PY = test/spork.py

all:
	python setup.py build

clean:
	-rm -rf build *~

install:
	python setup.py install

test:
	python $(TEST_PY)
