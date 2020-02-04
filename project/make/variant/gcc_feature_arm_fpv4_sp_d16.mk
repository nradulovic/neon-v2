#
# Neon
# Copyright (C) 2018   REAL-TIME CONSULTING
#

# Enable 
# mfloat-abi=hard: Uses floating-point instructions and the floating-point ABI
# fpv4: VFP version
# sp: single precision
# d16: 16 64-bit FPU registers
CC_FLAGS += --mfloat-abi=hard -mfpu=fpv4-sp-d16
LD_LIBS += m

