#
# Neon
# Copyright (C) 2018   REAL-TIME CONSULTING
#

# From: https://wiki.stm32duino.com/index.php?title=Blue_Pill
#
# Blue pill is the nickname given to the most popular, ultra-cheap and compact
# STM32F103 board. 

# Additional board description
BUILD_BOARD_DESC := "STM32F103 Blue Pill"

# Includes and sources
CC_SOURCES += lib/va_source/nport_board_stm32f103_blue_pill.c
CC_SOURCES += lib/va_source/nport_board_stm32f103_blue_pill_bsp.c
CC_INCLUDES += lib/va_include/nport/board_stm32f103_blue_pill

# This board will define the MCU
MCU := stm32f103c8

