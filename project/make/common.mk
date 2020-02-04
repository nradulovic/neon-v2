
# Common build variables
DEF_BUILD_DIR ?= generated

# Create possible targets
PROJECT_NAME   ?= undefined

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

# Set default rule to all
.DEFAULT_GOAL=all

.PHONY: clean-size
clean-size:
	$(PRINT) " [RM] " $(PROJECT_SIZE)
	$(VERBOSE)$(RMFILE) $(PROJECT_SIZE)

.PHONY: clean-flash
clean-flash:
	$(PRINT) " [RM] " $(PROJECT_FLASH)
	$(VERBOSE)$(RMFILE) $(PROJECT_FLASH)

.PHONY: clean-elf
clean-elf:
	$(PRINT) " [RM] " $(PROJECT_ELF)
	$(VERBOSE)$(RMFILE) $(PROJECT_ELF)

.PHONY: clean-lib
clean-lib:
	$(PRINT) " [RM] " $(PROJECT_LIB)
	$(VERBOSE)$(RMFILE) $(PROJECT_LIB)

.PHONY: clean-objects
clean-objects:
	$(PRINT) " [RM] " $(OBJECTS)
	$(VERBOSE)$(RMFILE) $(OBJECTS)
