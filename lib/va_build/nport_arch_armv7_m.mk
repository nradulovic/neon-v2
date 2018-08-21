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
ifndef VA_BUILD_NPORT_ARCH_ARMV7_M_MK
VA_BUILD_NPORT_ARCH_ARMV7_M_MK=1

# Architecture identifier
BUILD_ARCH = armv7_m

# Additional board description
BUILD_ARCH_DESC = "ARMv7-M Architecture"

CC_INCLUDES += lib/va_include/nport/arch_armv7_m

ifeq ($(BUILD_MCU_FAM),cortex-m3)
ADD_PLATFORM_FEATURE += cortex_m3
else ifeq ($(BUILD_MCU_FAM),cortex-m4)
ADD_PLATFORM_FEATURE += cortex_m4
else ifeq ($(BUILD_MCU_FAM),cortex-m7)
ADD_PLATFORM_FEATURE += cortex_m7
else
$(error Internal build error no such BUILD_MCU_FAM := $(BUILD_MCU_FAM))
endif

ifneq (,$(findstring fphard,$(BUILD_MCU_ATTR)))
ADD_PLATFORM_FEATURE += arm_fpv4_sp_d16
endif

NCONFIG_ARCH_ARMV7_M := 1

endif
