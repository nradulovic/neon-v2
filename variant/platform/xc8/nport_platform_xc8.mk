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
BUILD_PLATFORM_DESC = "Microchip XC8"

CC_INCLUDES += lib/va_include/nport/platform_xc8
# CC_SOURCES += lib/va_source/nport_platform_xc8.c

# Builder helper variables
OBJECTS          = $(patsubst %.c,$(DEF_BUILD_DIR)/%.o,$(CC_SOURCES))
OBJECTS         += $(patsubst %.S,$(DEF_BUILD_DIR)/%.o,$(AS_SOURCES))
DEPENDS          = $(patsubst %.o,%.d,$(OBJECTS))
PREPROCESSED     = $(patsubst %.o,%.i,$(OBJECTS))

# Convert compiler agnostic MCU layer information about used MCU to XC8 
# tool-chain MCU naming scheme. Compiler XC8 tool-chain expects the same string
# but with PIC part stripped.
CC_FLAGS += -mcpu=$(BUILD_MCU_DESC:PIC%=%) 

# Rule to compile C sources to preprocessed files.
$(DEF_BUILD_DIR)/%.i: $(WS)/%.c
	$(call print, [CP]: $@)
	$(VERBOSE)echo xc8-cc -mcpu

# Rule to compile C sources to object files.
$(DEF_BUILD_DIR)/%.o: $(WS)/%.c
	$(call print, [CC]: $@)
	$(VERBOSE)$(call mkdir, $(dir $@))
	$(VERBOSE)xc8-cc $(CC_FLAGS) \
	$(addprefix -D, $(CC_DEFINES)) \
        $(addprefix -I$(WS)/, $(CC_INCLUDES)) \
	-o $@ \
        -c $<

# Rule to compile Assembly sources to preprocessed files.
$(DEF_BUILD_DIR)/%.i: $(WS)/%.S
	$(call print, [AP]: $@)
	$(VERBOSE)$(call echo, Building with Microchip XC8 is not supported)

# Rule to compile Assembly sources to object files.
$(DEF_BUILD_DIR)/%.o: $(WS)/%.S
	$(call print, [AS]: $@)
	$(VERBOSE)$(call echo, Building with Microchip XC8 is not supported)

# Rule to link object files to library.
%.a:
	$(call print, [AR]: $@)
	$(VERBOSE)$(call echo, Building with Microchip XC8 is not supported)

# Rule to link object files to ELF executable.
%.elf: $(LD_LIBS) $(AR_LIBS)
	$(call print, [LD]: $@)
	$(VERBOSE)$(call echo, Building with Microchip XC8 is not supported)

# Rule to generate HEX file from ELF executable.
%.hex:
	$(call print, [OBJCOPY]: $@)
	$(VERBOSE)$(call echo, Building with Microchip XC8 is not supported)

# Rule to generate size report from ELF executable.
%.siz:
	$(call print, [SIZE]: $@)
	$(VERBOSE)$(call echo, Building with Microchip XC8 is not supported)

