
# Some defaults if they are not alredy given.
NPORT_NAME ?= generic
PROFILE ?= debug
PLATFORM ?= gcc

# Load specified port
include $(WS_DIR)/variant/nport_$(NPORT_NAME).mk

# NOTE: Load specified PROFILE
include $(WS_DIR)/variant/nprofile_$(PROFILE).mk

# NOTE: Load specified PLATFORM
include $(WS_DIR)/variant/nplatform_$(PLATFORM).mk

# From ADD_NPORT_FEATURE set substract DEL_NPORT_FEATURE set
NPORT_FEATURE_LIST = $(filter-out $(sort $(DEL_NPORT_FEATURE)), $(sort $(ADD_NPORT_FEATURE)))

# Include all filtered include files
NPORT_FEATURES = $(NPORT_FEATURE_LIST:%=$(WS_DIR)/build/$(PLATFORM)_feature_%.mk)

include $(NPORT_FEATURES)

CC_INCLUDES += neon
CC_SOURCES += source/core/nbits.c
