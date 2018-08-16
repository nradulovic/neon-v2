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
ifndef EXT_STM32CUBE_FW_F4_CMSIS
EXT_STM32CUBE_FW_F4_CMSIS=1

include $(WS)/ext/stm32cubef4/stm32cubef4.mk

CC_INCLUDES += $(STM32CUBEF4_PATH)/Drivers/CMSIS/Device/ST/STM32F4xx/Include
CC_INCLUDES += $(STM32CUBEF4_PATH)/Drivers/CMSIS/Include

endif
