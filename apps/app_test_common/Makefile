
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

TARGETS := narch nbits

.PHONY: all
all:
	@for t in $(TARGETS); do $(MAKE) -C $$t all; done

.PHONY: clean
clean:
	@for t in $(TARGETS); do $(MAKE) -C $$t clean; done

.PHONY: distclean
distclean:
	@for t in $(TARGETS); do $(MAKE) -C $$t distclean; done

.PHONY: config
config:
	@for t in $(TARGETS); do $(MAKE) -C $$t config; done

.PHONY: test
test:
	@for t in $(TARGETS); do $(MAKE) -C $$t test; done

