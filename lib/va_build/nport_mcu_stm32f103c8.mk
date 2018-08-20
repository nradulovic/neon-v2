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

# ARM 32-bit Cortex-M3 CPU Core
#
# * 72 MHz maximum frequency, 1.25 DMIPS/MHz (Dhrystone 2.1) performance at 0 
#   wait state memory access
# * Single-cycle multiplication and hardware division
# 
# Memories
#
# * 64 or 128 Kbytes of Flash memory
# * 20 Kbytes of SRAM
#

# MCU identifier
BUILD_MCU := stm32f103c8

# Additional MCU description
BUILD_MCU_DESC := "STM32F103C8"

# Additional MCU information
BUILD_MCU_FAM := generic
BUILD_MCU_ATTR :=

CC_SOURCES += lib/va_source/nport_mcu_generic.c
CC_INCLUDES += lib/va_include/nport/mcu_stm32f103c8

# This board will define the ARCH
ARCH = armv7_m

# Include MCU specific header paths and defines
include $(WS)/ext/stm32/stm32cubef1_stm32f103c8.mk
include $(WS)/ext/stm32/stm32cubef1_cmsis.mk