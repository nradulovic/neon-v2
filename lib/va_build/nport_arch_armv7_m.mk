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
CC_FLAGS += -march=armv7-m -mthumb

# This is the default architecture
ifeq ($(BUILD_MCU_FAM),generic)
CC_FLAGS += -mcpu=cortex-m3
endif

ifeq ($(BUILD_MCU_FAM),cortex-m3)
CC_FLAGS += -mcpu=cortex-m3
endif

ifeq ($(BUILD_MCU_FAM),cortex-m4)
CC_FLAGS += -mcpu=cortex-m4
endif

ifneq ($(filter fp=,$(BUILD_MCU_ATTR)),hard)
    $(info Using Hard floating pointer arithmetic.)
else
    $(info $(ENV_PARAM) does not exist in $(PARAMS))
endif

PREFIX = arm-none-eabi-

NCONFIG_ARCH_ARMV7_M := 1

endif
