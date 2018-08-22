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

# Include guard
ifndef LIB_BUILD_NPORT_MK
LIB_BUILD_NPORT_MK=1

# Dependencies
include $(WS)/lib/build/nlib.mk

# Some defaults if they are not alredy given.
BOARD ?= generic
MCU ?= generic
CORE ?= x86
ARCH ?= x86
PLATFORM ?= gcc
PROFILE ?= debug
OS ?= linux

# NOTE: Load specified board
err=$(call safe_include, $(WS)/lib/va_build/nport_board_$(BOARD).mk)

ifneq ($(err),)
$(shell echo "[BUILD]: No board support was found for '$(BOARD)'\n" \
			 "\n" \
			 "Please, try any of the following steps:\n" \
			 " * Create the board from nport_board_generic.mk\n" \
			 " * Create ticket to upstream for support\n" \
			 " * Check if the board name is correctly typed" > /dev/stderr)
$(error No board support was found for '$(BOARD)')
endif

# NOTE: Load specified MCU
include $(WS)/lib/va_build/nport_mcu_$(MCU).mk
-include $(WS)/lib/va_build/$(PLATFORM)_mcu_$(MCU).mk

# NOTE: Load specified CORE
include $(WS)/lib/va_build/nport_core_$(CORE).mk
-include $(WS)/lib/va_build/$(PLATFORM)_core_$(CORE).mk

# NOTE: Load specified ARCH
include $(WS)/lib/va_build/nport_arch_$(ARCH).mk
-include $(WS)/lib/va_build/$(PLATFORM)_arch_$(ARCH).mk

# NOTE: Load specified OS
include $(WS)/lib/va_build/nport_os_$(OS).mk
-include $(WS)/lib/va_build/$(PLATFORM)_os_$(OS).mk

# NOTE: Load specified PROFILE
include $(WS)/lib/va_build/nport_profile_$(PROFILE).mk
-include $(WS)/lib/va_build/$(PLATFORM)_profile_$(PROFILE).mk

# NOTE: Load specified PLATFORM
include $(WS)/lib/va_build/nport_platform_$(PLATFORM).mk

# From ADD_NPORT_FEATURE set substract DEL_NPORT_FEATURE set
NPORT_FEATURE_LIST = $(filter-out $(sort $(DEL_NPORT_FEATURE)), $(sort $(ADD_NPORT_FEATURE)))

# Include all filtered include files
NPORT_FEATURES = $(NPORT_FEATURE_LIST:%=$(WS)/lib/va_build/$(PLATFORM)_feature_%.mk)

endif
