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
all: apps 
 
.PHONY: clean
clean: apps-clean 

.PHONY: distclean
distclean: apps-distclean 

# Application handling

.PHONY: apps
apps: apps-config
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

.PHONY: apps-config
apps-config:
	@for app in apps/app_*/; \
    do \
        if [ -d $${app} ]; then $(MAKE) -C $${app} config; fi; \
    done

# Tests handling
.PHONY: test
test: all
	@for app in apps/app_test_*/; \
    do \
        if [ -d $${app} ]; then $(MAKE) -C $${app} test; fi; \
    done
	

