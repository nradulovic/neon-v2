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
ifndef LIB_BUILD_NBITS_MK
LIB_BUILD_NBITS_MK=1

# Dependencies
include $(WS)/nk/build/common.mk

ifneq ("$(PROJECT_CONFIG)","")
$(info Using Application config: $(PROJECT_CONFIG))
CC_DEFINES += NEON_APP_CONFIG=\"$(PROJECT_CONFIG)\"
endif

# Some defaults if they are not already given.
ARCH ?= x86
CPU ?= x86
PLATFORM ?= gcc
PROFILE ?= debug
OS ?= linux

# NOTE: Load specified CPU
include $(WS)/nk/va_build/nport_cpu_$(CPU).mk
-include $(WS)/nk/va_build/$(PLATFORM)_cpu_$(CPU).mk

# NOTE: Load specified ARCH
include $(WS)/nk/va_build/nport_arch_$(ARCH).mk
-include $(WS)/nk/va_build/$(PLATFORM)_arch_$(ARCH).mk

# NOTE: Load specified OS
include $(WS)/nk/va_build/nport_os_$(OS).mk
-include $(WS)/nk/va_build/$(PLATFORM)_os_$(OS).mk

# NOTE: Load specified PROFILE
include $(WS)/nk/va_build/nport_profile_$(PROFILE).mk
-include $(WS)/nk/va_build/$(PLATFORM)_profile_$(PROFILE).mk

# NOTE: Load specified PLATFORM
include $(WS)/nk/va_build/nport_platform_$(PLATFORM).mk

# From ADD_NPORT_FEATURE set substract DEL_NPORT_FEATURE set
NPORT_FEATURE_LIST = $(filter-out $(sort $(DEL_NPORT_FEATURE)), $(sort $(ADD_NPORT_FEATURE)))

# Include only filtered include files
NPORT_FEATURES = $(NPORT_FEATURE_LIST:%=$(WS)/nk/va_build/$(PLATFORM)_feature_%.mk)

# Add common library include folder
CC_INCLUDES += nk/include
CC_SOURCES += nk/source/neon.c

endif
