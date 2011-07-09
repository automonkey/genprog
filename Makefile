
.PHONY: all dep clean test default

default: all test

all: genproglib genproglibut

include global.mk

Dir := genproglib
include genproglib/genproglib.mk

Dir := genproglibut
include genproglibut/genproglibut.mk

include $(DEP_FILES)

dep: $(DEP_FILES)

clean:
	-rm $(CLEAN_FILES)

test: $(TEST_FILES)
	@for tst in $^; do echo Running test $$tst; $$tst; done;
