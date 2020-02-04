#
# Neon
# Copyright (C) 2018   REAL-TIME CONSULTING
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

# Additional MCU description
BUILD_MCU_DESC := "STM32F103C8"

# Includes and sources
CC_SOURCES += lib/va_source/nport_mcu_generic.c
CC_INCLUDES += lib/va_include/nport/mcu_stm32f103c8

# Include MCU specific header paths and defines
include $(WS)/ext/stm32/stm32cubef1_stm32f103c8.mk
include $(WS)/ext/stm32/stm32cubef1_cmsis.mk

# This mcu will define the core
CORE = cortex_m3

