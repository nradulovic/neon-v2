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

# Generic rules

.PHONY: all
all: apps templates tests
 
.PHONY: clean
clean: apps-clean templates-clean tests-clean

.PHONY: distclean
distclean: apps-distclean templates-distclean tests-distclean

.PHONY: test
test: all
	@./test/generated/test.elf

# Application handling

.PHONY: apps
apps:
	@for app in apps/app_*/; \
    do \
        if [ -d $${app} ]; then $(MAKE) -C $${app} all; fi; \
    done

.PHONY: apps-clean
apps-clean:
	@for app in apps/app_*/; \
    do \
        if [ -d $${app} ]; then $(MAKE) -C $${app} clean; fi; \
    done

.PHONY: apps-distclean
apps-distclean:
	@for app in apps/app_*/; \
    do \
        if [ -d $${app} ]; then $(MAKE) -C $${app} distclean; fi; \
    done

# Template handling

.PHONY: templates
templates:
	@for template in templates/app_*/; do $(MAKE) -C $${template} all; done

.PHONY: templates-clean
templates-clean:
	@for template in templates/app_*/; do $(MAKE) -C $${template} clean; done

.PHONY: templates-distclean
templates-distclean:
	@for template in templates/app_*/; do $(MAKE) -C $${template} distclean; done

# Tests handling

.PHONY: tests
tests:
	@$(MAKE) -C test all; done

.PHONY: tests-clean
tests-clean:
	@$(MAKE) -C test clean; done

.PHONY: tests-distclean
tests-distclean:
	@$(MAKE) -C test distclean; done
