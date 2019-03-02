#
# Neon
# Copyright (C) 2018   REAL-TIME CONSULTING
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

# Platform description
BUILD_PLATFORM_DESC = "GCC, the GNU Lesser Compiler Collection"

# Builder helper variables
OBJECTS          = $(patsubst %.c,$(DEF_BUILD_DIR)/%.o,$(CC_SOURCES))
OBJECTS         += $(patsubst %.S,$(DEF_BUILD_DIR)/%.o,$(AS_SOURCES))
DEPENDS          = $(patsubst %.o,%.d,$(OBJECTS))
PREPROCESSED     = $(patsubst %.o,%.i,$(OBJECTS))

CC_INCLUDES += lib/va_include/nport/platform_gcc
CC_SOURCES += lib/va_source/nport_platform_gcc.c
CC_FLAGS += -std=c99 -fmessage-length=0
CC_FLAGS += -Wall -Wextra -pedantic -Wconversion

SIZ_FORMAT=Berkeley
FLASH_FORMAT=ihex

# Builder variables
CC              = $(PREFIX)gcc
LD              = $(PREFIX)gcc
OBJCOPY         = $(PREFIX)objcopy
SIZE            = $(PREFIX)size
AR              = $(PREFIX)ar

# Rule to compile C sources to object files.
$(DEF_BUILD_DIR)/%.o: $(WS)/%.c
	$(call print, [CC]: $@)
	$(VERBOSE)$(call mkdir, $(dir $@))
	$(VERBOSE)$(CC) $(CC_FLAGS) \
	    $(addprefix -D, $(CC_DEFINES)) \
	    $(addprefix -I$(WS)/, $(CC_INCLUDES)) \
	    -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" \
	    -o $@ \
	    -c $<

# Rule to compile C sources to preprocessed files.
$(DEF_BUILD_DIR)/%.i: $(WS)/%.c
	$(call print, [CP]: $@)
	$(VERBOSE)$(call mkdir, $(dir $@))
	$(VERBOSE)$(CC) $(CC_FLAGS) \
	    $(addprefix -D, $(CC_DEFINES)) \
	    $(addprefix -I$(WS)/, $(CC_INCLUDES)) \
	    -o $@ \
	    -E $<

# Rule to compile Assembly sources to preprocessed files.
$(DEF_BUILD_DIR)/%.i: $(WS)/%.S
	$(call print, [AP]: $@)
	$(VERBOSE)$(call mkdir, $(dir $@))
	$(VERBOSE)$(CC) $(CC_FLAGS) \
	    $(addprefix -D, $(CC_DEFINES)) \
	    $(addprefix -I$(WS)/, $(CC_INCLUDES)) \
	    -o $@ \
	    -E $<

# Rule to compile Assembly sources to object files.
$(DEF_BUILD_DIR)/%.o: $(WS)/%.S
	$(call print, [AS]: $@)
	$(VERBOSE)$(call mkdir, $(dir $@))
	$(VERBOSE)$(CC) $(CC_FLAGS) \
        $(addprefix -D, $(CC_DEFINES)) \
        $(addprefix -I$(WS)/, $(CC_INCLUDES)) \
        -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" \
        -o $@ \
        -c $<

# Rule to link object files to library.
%.a:
	$(call print, [AR]: $@)
	$(VERBOSE)$(AR) rcs $(AR_FLAGS) $@ \
	    $^ \
	    $(AR_LIBS)

# Rule to link object files to ELF executable.
%.elf: $(LD_LIBS) $(AR_LIBS)
	$(call print, [LD]: $@)
	$(VERBOSE)$(LD) $(LD_FLAGS) -o $@ -Xlinker $^ $(LD_LIBS) $(AR_LIBS)

# Rule to generate HEX file from ELF executable.
%.hex:
	$(call print, [OBJCOPY]: $@)
	$(VERBOSE)$(OBJCOPY) -O $(FLASH_FORMAT) $< $@

# Rule to generate size report from ELF executable.
%.siz:
	$(call print, [SIZE]: $@)
	$(VERBOSE)$(SIZE) --format=$(SIZ_FORMAT) $< > $@
	$(VERBOSE)cat $@

# TODO: See https://launchpadlibrarian.net/170926122/readme.txt
