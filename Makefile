#
# Neon
# Copyright (C) 2018   REAL-TIME CONSULTING
#
# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
# more details.
#
# You should have received a copy of the GNU Lesser General Public License along with
# this program. If not, see <http://www.gnu.org/licenses/>.
#

SUBDIRS := apps/app_test apps/app_template apps/app_hello_world

BUILD_TARGETS     := $(addsuffix -build,     $(SUBDIRS))
CLEAN_TARGETS     := $(addsuffix -clean,     $(SUBDIRS))
DISTCLEAN_TARGETS := $(addsuffix -distclean, $(SUBDIRS))
CONFIG_TARGETS    := $(addsuffix -config,    $(SUBDIRS))
TEST_TARGETS      := $(addsuffix -test,      $(SUBDIRS))
	
# Generic rules

.PHONY: all
all: build
	
.PHONY: build
build: $(BUILD_TARGETS)
 
.PHONY: clean
clean: $(CLEAN_TARGETS)

.PHONY: distclean
distclean: $(DISTCLEAN_TARGETS)
	
.PHONY: config
config: $(CONFIG_TARGETS)

.PHONY: test
test: $(TEST_TARGETS)

.PHONY: $(BUILD_TARGETS)
$(BUILD_TARGETS):
	$(MAKE) -C $(@:%-build=%) build

.PHONY: $(CLEAN_TARGETS)
$(CLEAN_TARGETS):
	$(MAKE) -C $(@:%-clean=%) clean
	
.PHONY: $(DISTCLEAN_TARGETS)
$(DISTCLEAN_TARGETS):
	$(MAKE) -C $(@:%-distclean=%) distclean

.PHONY: $(CONFIG_TARGETS)
$(CONFIG_TARGETS):
	$(MAKE) -C $(@:%-config=%) config
	
.PHONY: $(TEST_TARGETS)
$(TEST_TARGETS):
	$(MAKE) -C $(@:%-test=%) test
