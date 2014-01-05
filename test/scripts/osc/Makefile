CHUCK=/usr/bin/chuck
CLASSES := OscTestRunner.ck OscTest.ck

TESTS := int \
         float \
         string \
         two-args \
         single-char-match \
         star-match \
         charclass-match \
         charclass-range-match \
         charclass-negate-match \
         stringlist

TESTS := $(addsuffix -test,$(TESTS))

.PHONY: all $(TESTS)

all: $(TESTS)

see:
	@echo $(TESTS)

run-test = $(CHUCK) $(CLASSES) $(addsuffix .ck,$@)

int-test:
	@$(run-test)

float-test:
	@$(run-test)

string-test:
	@$(run-test)

two-args-test:
	@$(run-test)

single-char-match-test:
	@$(run-test)

star-match-test:
	@$(run-test)

charclass-match-test:
	@$(run-test)

charclass-range-match-test:
	@$(run-test)

charclass-negate-match-test:
	@$(run-test)

stringlist-test:
	@$(run-test)