#
# Neon
# Copyright (C) 2018   REAL-TIME CONSULTING
#

# Platform description
BUILD_PLATFORM_DESC = "GCC, the GNU Lesser Compiler Collection"

CC_FLAGS += -std=c99 -fmessage-length=0
CC_FLAGS += -Wall -Wextra -pedantic

CC_SOURCES += neon/variant/platform/gcc/gcc_platform.c

SIZ_FORMAT=Berkeley
FLASH_FORMAT=ihex

PROJECT_ELF     = $(DEF_BUILD_DIR)/$(PROJECT_NAME).elf
PROJECT_LIB     = $(DEF_BUILD_DIR)/$(PROJECT_NAME).a
PROJECT_FLASH   = $(DEF_BUILD_DIR)/$(PROJECT_NAME).hex
PROJECT_SIZE    = $(DEF_BUILD_DIR)/$(PROJECT_NAME).siz

# Builder helper variables
OBJECTS          = $(patsubst %.c,$(DEF_BUILD_DIR)/%.o,$(CC_SOURCES))
OBJECTS         += $(patsubst %.S,$(DEF_BUILD_DIR)/%.o,$(AS_SOURCES))
DEPENDS          = $(patsubst %.o,%.d,$(OBJECTS))
PREPROCESSED     = $(patsubst %.o,%.i,$(OBJECTS))

# Builder variables
CC              = $(PREFIX)gcc
LD              = $(PREFIX)gcc
OBJCOPY         = $(PREFIX)objcopy
SIZE            = $(PREFIX)size
AR              = $(PREFIX)ar
MKDIR           = mkdir -p
RMDIR           = rm -rf
RMFILE          = rm -f

# Rule to compile C sources to object files.
$(DEF_BUILD_DIR)/%.o: $(NEON_DIR)/%.c 
	$(PRINT) " [CC]: $@"
	$(VERBOSE)$(MKDIR) $(dir $@)
	$(VERBOSE)$(CC) $(CC_FLAGS) \
        $(addprefix -D, $(CC_DEFINES)) \
        $(addprefix -I$(NEON_DIR)/, $(CC_INCLUDES)) \
        -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" \
        -o $@ \
        -c $<

# Rule to compile C sources to preprocessed files.
$(DEF_BUILD_DIR)/%.i: $(NEON_DIR)/%.c
	$(PRINT) " [CC]: $@"
	$(VERBOSE)$(MKDIR) $(dir $@)
	$(VERBOSE)$(CC) $(CC_FLAGS) \
        $(addprefix -D, $(CC_DEFINES)) \
        $(addprefix -I$(NEON_DIR)/, $(CC_INCLUDES)) \
        -o $@ \
        -E $<

# Rule to compile Assembly sources to preprocessed files.
$(DEF_BUILD_DIR)/%.i: $(NEON_DIR)/%.S
	$(PRINT) " [AS]: $@"
	$(VERBOSE)$(MKDIR) $(dir $@)
	$(VERBOSE)$(CC) $(CC_FLAGS) \
        $(addprefix -D, $(CC_DEFINES)) \
        $(addprefix -I$(NEON_DIR)/, $(CC_INCLUDES)) \
        -o $@ \
        -E $<

# Rule to compile Assembly sources to object files.
$(DEF_BUILD_DIR)/%.o: $(NEON_DIR)/%.S
	$(PRINT) " [AS]: $@"
	$(VERBOSE)$(MKDIR) $(dir $@)
	$(VERBOSE)$(CC) $(CC_FLAGS) \
        $(addprefix -D, $(CC_DEFINES)) \
        $(addprefix -I$(NEON_DIR)/, $(CC_INCLUDES)) \
        -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" \
        -o $@ \
        -c $<

# Rule to link object files to library.
%.a:
	$(PRINT) " [AR]: $@"
	$(VERBOSE)$(AR) rcs $(AR_FLAGS) $@ \
        $^ \
        $(AR_LIBS)

# Rule to link object files to ELF executable.
%.elf: $(LD_LIBS) $(AR_LIBS)
	$(PRINT) " [LD]: $@"
	$(VERBOSE)$(LD) $(LD_FLAGS) -o $@ -Xlinker $^ $(LD_LIBS) $(AR_LIBS)

# Rule to generate HEX file from ELF executable.
%.hex:
	$(PRINT) " [OBJCOPY]: $@"
	$(VERBOSE)$(OBJCOPY) -O $(FLASH_FORMAT) $< $@

# Rule to generate size report from ELF executable.
%.siz:
	$(PRINT) " [SIZE]: $@"
	$(VERBOSE)$(SIZE) --format=$(SIZ_FORMAT) $< > $@
	$(VERBOSE)cat $@

# TODO: See https://launchpadlibrarian.net/170926122/readme.txt
