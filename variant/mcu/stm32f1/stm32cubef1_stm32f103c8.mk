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
ifndef EXT_STM32_STM32CUBE_FW_F1_STM32F103C8
EXT_STM32_STM32CUBE_FW_F1_STM32F103C8=1

include $(WS)/ext/stm32/stm32cubef1.mk

# Add folder to common MCU headers
CC_INCLUDES += $(STM32CUBEF1_PATH)/Drivers/CMSIS/Device/ST/STM32F1xx/Include
CC_INCLUDES += $(STM32CUBEF1_PATH)/Drivers/STM32F1xx_HAL_Driver/Inc
CC_SOURCES += $(STM32CUBEF1_PATH)/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c

# Select appropriate STM32 header
CC_DEFINES += STM32F103xB  

# Enable STM32 HAL Driver
CC_DEFINES += USE_HAL_DRIVER  

# HAL driver needs support files
CC_INCLUDES += $(STM32CUBEF1_PATH)/../support/stm32f1

# Add startup code

ifeq ($(PLATFORM), gcc)
LD_FLAGS += -T $(WS)/$(STM32CUBEF1_PATH)/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/linker/STM32F103XB_FLASH.ld
AS_SOURCES += $(STM32CUBEF1_PATH)/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/startup_stm32f103xb.S
else ifeq ($(PLATFORM), arm)
AS_SOURCES += $(STM32CUBEF1_PATH)/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/arm/startup_stm32f103xb.S
else ifeq ($(PLATFORM), iar)
AS_SOURCES += $(STM32CUBEF1_PATH)/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/iar/startup_stm32f103xb.S
LD_FLAGS += -T $(WS)/$(STM32CUBEF1_PATH)/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/iar/linker/stm32f103xb_flash.icf
else
$(error Selected platform $(PLATFORM) is not supported by $(STM32CUBEF1_NAME))
endif

LD_FLAGS += --specs=nosys.specs
endif
