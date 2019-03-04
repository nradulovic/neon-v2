#
# Neon
# Copyright (C)  2017  Nenad Radulovic
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
ifndef EXT_STM32CUBE_FW_F4
EXT_STM32CUBE_FW_F4=1

STM32CUBEF4_NAME := STM32 Cube F4

#
# WARNING WARNING WARNING
#
# We are using firstword function here. This means that the STM32CUBEF4_PATH
# variable will fail to resolve properly if there is a space in path.
STM32CUBEF4_PATH = $(firstword $(wildcard $(WS)/ext/stm32/STM32Cube_FW_F4*))

ifeq ("$(STM32CUBEF4_PATH)", "")
$(error [EXT]: No $(STM32CUBEF4_NAME) library was found in ext/stm32)
endif

ifeq ("$(V)", "1")
$(info $(STM32CUBEF4_NAME) in $(STM32CUBEF4_PATH))
endif

endif
