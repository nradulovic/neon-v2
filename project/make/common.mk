
# Common build variables
DEF_BUILD_DIR ?= generated

# Create possible targets
PROJECT_NAME   ?= undefined
PROJECT_ELF     = $(DEF_BUILD_DIR)/$(PROJECT_NAME).elf
PROJECT_LIB     = $(DEF_BUILD_DIR)/$(PROJECT_NAME).a
PROJECT_FLASH   = $(DEF_BUILD_DIR)/$(PROJECT_NAME).hex
PROJECT_SIZE    = $(DEF_BUILD_DIR)/$(PROJECT_NAME).siz

# Builder helper variables
OBJECTS          = $(patsubst %.c,$(DEF_BUILD_DIR)/%.o,$(CC_SOURCES))
OBJECTS         += $(patsubst %.S,$(DEF_BUILD_DIR)/%.o,$(AS_SOURCES))
DEPENDS          = $(patsubst %.o,%.d,$(OBJECTS))
PREPROCESSED     = $(patsubst %.o,%.i,$(OBJECTS))

# Handle the verbosity argument
# If the argument is not given assume that verbosity is off.
V ?= 0
ifeq ("$(V)","1")
VERBOSE         := # Empty space
PRINT           := @true # Empty space
else ifeq ("$(V)","0")
VERBOSE         := @ # Empty space
PRINT           := @echo # Empty space
MAKEFLAGS       += -s
else
$(error Specify either `V=0` or `V=1`)
endif

include $(WS_DIR)/library.mk

# This is the default target
.PHONY: all
all:

.PHONY: clean
clean:

.PHONY: clean-objects
clean-objects: 
	$(VERBOSE)rm -f $(OBJECTS) $(DEPENDS)

.PHONY: clean-lib
clean-lib: clean-objects
	$(PRINT) "Cleaning library..."
	$(VERBOSE)rm -rf $(PROJECT_LIB)

.PHONY: clean-elf
clean-elf: clean-lib
	$(PRINT) "Cleaning executable..."
	$(VERBOSE)rm -rf $(PROJECT_ELF)

.PHONY: clean-size
clean-size: clean-elf
	$(PRINT) "Cleaning size report..."
	$(VERBOSE)rm -rf $(PROJECT_SIZE)

.PHONY: clean-flash
clean-flash: clean-elf
	$(PRINT) "Cleaning flash binary file..."
	$(VERBOSE)rm -rf $(PROJECT_FLASH)
