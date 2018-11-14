
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

# Relative path to common build directory.
WS = ../../..

# Relative path to this project directory.
PROJECT_DIR = apps/app_test/ndebug_enabled

# Project name, this will be used as output binary file name.
PROJECT_NAME := test_ndebug_enabled

# Project configuration header file.
PROJECT_CONFIG := $(PROJECT_DIR)/../include/config_ndebug_enable.h

# Include depenencies, nport is needed to import additional build rules.
include $(WS)/lib/build/nbits.mk
include $(WS)/lib/build/ntestsuite.mk

# List additional C header include paths.
CC_INCLUDES += $(PROJECT_DIR)/../include

# List additional C source files. Files which are not listed here will not be
# compiled.
CC_SOURCES += $(PROJECT_DIR)/../source/main.c
CC_SOURCES += $(PROJECT_DIR)/../source/test_ndebug_enabled.c

# List additional archives. Use this when using an external static archive.
AR_LIBS +=

# List additional libraries. Use this when using an external static library.
LD_LIBS +=

# Include configurable nport feature makefiles
include ../common/common.mk
