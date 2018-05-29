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

# Relative path to common build directory
WS = ../..

# Common build script
include $(WS)/build/common.mk

# Include depenencies
include $(WS)/lib/build/nlib.mk
include $(WS)/lib/build/nport.mk

# Define project name
PROJECT_NAME := app_template

# List additional includes
CC_INCLUDES += templates/app_template/include

# List additional sources
CC_SOURCES += templates/app_template/source/main.c

# List additional archives
AR_LIBS +=

# List additional libraries
LD_LIBS +=

all: $(PROJECT_ELF)

clean: clean-objects

distclean: 
	$(VERBOSE)rm -rf $(BUILD_DIR)

$(PROJECT_LIB): $(OBJECTS)

$(PROJECT_ELF): $(PROJECT_LIB)

-include $(DEPENDS)
