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

