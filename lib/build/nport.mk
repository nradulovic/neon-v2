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
include $(WS)/lib/build/common.mk

# Some defaults if they are not already given.
BOARD ?= generic
MCU ?= generic
CORE ?= x86
ARCH ?= x86
PLATFORM ?= gcc
PROFILE ?= debug
TARGET_OS ?= linux

ifeq ($(OS),Windows_NT)
HOST_OS := windows
else
HOST_OS := linux
endif

include $(WS)/lib/va_build/nport_host_os_$(HOST_OS).mk

# NOTE: Load specified board
BOARD_FILE := $(WS)/lib/va_build/nport_board_$(BOARD).mk
	
ifneq ("$(wildcard $(BOARD_FILE))","")
include $(BOARD_FILE)
else
$(info Please, try any of the following steps:)
$(info  * Create the board from nport_board_$(BOARD).mk)
$(info  * Create ticket to upstream for support)
$(info  * Check if the board name is correctly typed)
$(error [BUILD]: No board support was found for '$(BOARD)')
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
include $(WS)/lib/va_build/nport_target_os_$(TARGET_OS).mk
-include $(WS)/lib/va_build/$(PLATFORM)_target_os_$(TARGET_OS).mk

# NOTE: Load specified PROFILE
include $(WS)/lib/va_build/nport_profile_$(PROFILE).mk
-include $(WS)/lib/va_build/$(PLATFORM)_profile_$(PROFILE).mk

# NOTE: Load specified PLATFORM
include $(WS)/lib/va_build/nport_platform_$(PLATFORM).mk

# From ADD_NPORT_FEATURE set subtract DEL_NPORT_FEATURE set
NPORT_FEATURE_LIST = $(filter-out $(sort $(DEL_NPORT_FEATURE)), $(sort $(ADD_NPORT_FEATURE)))

# Include all filtered include files
NPORT_FEATURES = $(NPORT_FEATURE_LIST:%=$(WS)/lib/va_build/$(PLATFORM)_feature_%.mk)

endif
