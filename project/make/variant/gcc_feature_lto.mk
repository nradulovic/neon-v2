#
# Neon
# Copyright (C) 2018   REAL-TIME CONSULTING
#

CC_FLAGS += -flto
AR_FLAGS += --plugin lto
LD_FLAGS += -Wl,-flto
