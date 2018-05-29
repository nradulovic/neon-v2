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

# Some defaults if they are not alredy given.
BOARD ?= generic
MCU ?= generic
ARCH ?= x86
PLATFORM ?= gcc
PROFILE ?= debug
OS ?= linux

# Try to load specified board
-include $(WS)/lib/va_build/nport/nport_board_$(BOARD).mk

ifndef BUILD_BOARD
$(error The '$(BOARD)' board definition does not exists in Neon Port)
endif

# Try to load specified MCU
-include $(WS)/lib/va_build/nport/nport_mcu_$(MCU).mk

ifndef BUILD_MCU
$(error The '$(MCU)' MCU definition does not exists in Neon Port)
endif

# Try to load specified ARCH
-include $(WS)/lib/va_build/nport/nport_arch_$(ARCH).mk

ifndef BUILD_ARCH
$(error The '$(ARCH)' architecture definition does not exists in Neon Port)
endif

# Try to load specified PLATFORM
-include $(WS)/lib/va_build/nport/nport_platform_$(PLATFORM).mk

ifndef BUILD_PLATFORM
$(error The '$(PLATFORM)' platform definition does not exists in Neon Port)
endif

# Try to load specified PROFILE
-include $(WS)/lib/va_build/nport/nport_profile_$(PLATFORM)_$(PROFILE).mk

ifndef BUILD_PROFILE
$(error The '$(PROFILE)' profile definition does not exists in Neon Port)
endif

# Try to load specified OS
-include $(WS)/lib/va_build/nport/nport_os_$(OS).mk

ifndef BUILD_OS
$(error The '$(OS)' os definition does not exists in Neon Port)
endif

CFG_GIT_VERSION := $(shell git describe --abbrev=7 --always --dirty --tags 2>/dev/null || echo "unknown")

$(foreach v, $(filter CFG_%,$(.VARIABLES)), $(info $(v) = $($(v))))

