#
# Neon
# Copyright (C) 2018   REAL-TIME CONSULTING
#

# Additional board description
BUILD_ARCH_DESC = "Microchip PIC18 arhitecture"

# Define platform for this architecture
PLATFORM := xc8

# Includes and sources
CC_INCLUDES += lib/va_include/nport/arch_pic18
