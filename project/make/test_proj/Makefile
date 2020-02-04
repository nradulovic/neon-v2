#
# Neon
# Copyright (C) 2018   REAL-TIME CONSULTING
#

TARGETS := nport nbits

.PHONY: all
all: 
	@for t in $(TARGETS); do $(MAKE) -C $$t all || exit; done

.PHONY: clean
clean:
	@for t in $(TARGETS); do $(MAKE) -C $$t clean || exit; done

.PHONY: distclean
distclean:
	@for t in $(TARGETS); do $(MAKE) -C $$t distclean || exit; done

.PHONY: test
test: all
	@for t in $(TARGETS); do $(MAKE) -C $$t test || exit; done
