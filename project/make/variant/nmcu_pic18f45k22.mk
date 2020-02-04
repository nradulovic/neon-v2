#
# Neon
# Copyright (C) 2018   REAL-TIME CONSULTING
#

# NOTE:
# This is a generic MCU placeholder. It does not provide any functionality,
# it just creates dummy BSP implementation to satisfy linking.

# Additional MCU description
BUILD_MCU_DESC := "PIC18F45K22 MCU"

# Includes and sources
CC_SOURCES += lib/va_source/nport_mcu_generic.c
CC_INCLUDES += lib/va_include/nport/mcu_pic18f45k22

# Define core
CORE := pic18

