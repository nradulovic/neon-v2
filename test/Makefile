#
# Neon
# Copyright (C)  2017  Nenad Radulovic
#
# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
# more details.
#
# You should have received a copy of the GNU General Public License along with
# this program. If not, see <http://www.gnu.org/licenses/>.
#

# Relative path to nbase project
WS = ..

include $(WS)/build/common.mk
include $(WS)/lib/build/nlib.mk
include $(WS)/lib/build/nport.mk
include $(WS)/lib/build/nlogger.mk
include $(WS)/lib/build/ndebug.mk
include $(WS)/lib/build/nbits.mk
include $(WS)/lib/build/ntestsuite.mk

PROJECT_NAME := test
CC_INCLUDES += test/include
CC_SOURCES += test/source/main.c
CC_SOURCES += test/source/test_narch.c
CC_SOURCES += test/source/test_nlist_sll.c
CC_SOURCES += test/source/test_nlist_dll.c
CC_SOURCES += test/source/test_ndebug_enabled.c
CC_SOURCES += test/source/test_ndebug_disabled.c
CC_SOURCES += test/source/test_nbits.c
CC_SOURCES += test/source/test_nbitarray.c

all: $(PROJECT_ELF)

clean: clean-objects

distclean: 
	$(VERBOSE)rm -rf $(BUILD_DIR)

$(PROJECT_LIB): $(OBJECTS)

$(PROJECT_ELF): $(PROJECT_LIB)

-include $(DEPENDS)
