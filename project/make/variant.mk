
# Some defaults if they are not alredy given.
PORT_NAME ?= generic
PORT_PROFILE ?= debug
PORT_PLATFORM ?= gcc

# Load specified port
include $(WS_DIR)/variant/nport_$(PORT_NAME).mk

# NOTE: Load specified PROFILE
include $(WS_DIR)/variant/nprofile_$(PORT_PROFILE).mk
include $(WS_DIR)/variant/$(PORT_PLATFORM)_profile_$(PORT_PROFILE).mk

# NOTE: Load specified PLATFORM
include $(WS_DIR)/variant/nplatform_$(PORT_PLATFORM).mk

# From ADD_NPORT_FEATURE set substract DEL_NPORT_FEATURE set
PORT_FEATURE_LIST = $(filter-out $(sort $(DEL_PORT_FEATURE)), $(sort $(ADD_PORT_FEATURE)))

# Include all filtered include files
PORT_FEATURES = $(PORT_FEATURE_LIST:%=$(WS_DIR)/variant/$(PORT_PLATFORM)_feature_%.mk)

include $(PORT_FEATURES)

CC_INCLUDES += neon
CC_SOURCES += neon/core/nport.c
