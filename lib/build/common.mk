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

ifndef LIB_BUILD_COMMON_MK
LIB_BUILD_COMMON_MK = 1

# == Functions ==
# Check that given variables are set and all have non-empty values,
# die with an error otherwise.
#
# Params:
#   1. Variable name(s) to test.
#   2. (optional) Error message to print.
check_defined = \
    $(strip $(foreach 1,$1, \
            $(call __check_defined,$1,$(strip $(value 2)))))
    __check_defined = \
        $(if $(value $1),, \
              $(error Undefined $1$(if $2, ($2))))

# Try to include a file given in the first argument. The function will return
# the status which must be checked.
#
# Params:
#   1. Include file name
safe_include = \
    $(if $(shell if [ -e $1 ]; then echo 1; fi),$(eval include $1), \
        $(shell echo $1))

$(call check_defined, WS, WS is relative path to Neon build directory)
$(call check_defined, PROJECT_DIR, PROJECT_DIR is project root source directory)
$(call check_defined, PROJECT_NAME, PROJECT_NAME is project name)

# Documentation defaults
DEF_DOX_O        = documentation/generated
DEF_DOX_HTML_O   = html
DEF_DOX_LATEX_O  = latex
DEF_DOX_PROJECT  = documentation/$(MOD_NAME)_doxyfile
DEF_DOX_BASE     = $(WS)/documentation/base_doxyfile
DEF_DOXYFILE	 = $(DEF_DOX_O)/doxyfile

# Common build variables
DEF_BUILD_DIR   = generated
DEF_PACK_DIR    = packed

# Create possible targets
PROJECT_NAME   ?= undefined
PROJECT_ELF     = $(DEF_BUILD_DIR)/$(PROJECT_NAME).elf
PROJECT_LIB     = $(DEF_BUILD_DIR)/$(PROJECT_NAME).a
PROJECT_FLASH   = $(DEF_BUILD_DIR)/$(PROJECT_NAME).hex
PROJECT_SIZE    = $(DEF_BUILD_DIR)/$(PROJECT_NAME).siz
PROJECT_CONFIG ?= lib/include/configs/default_config.h

# Library header configuration
CC_CONFIG_FILE = $(DEF_BUILD_DIR)/neon_config.h

# Handle the verbosity argument
# If the argument is not given assume that verbosity is off.
V ?= 0
ifeq ("$(V)","1")
VERBOSE         := # Empty space
print           := # Empty space
else ifeq ("$(V)","0")
VERBOSE         := @ # Empty space
print		 = $(call echo,$(1))
MAKEFLAGS       += -s
else
$(error Specify either `V=0` or `V=1`)
endif

# This is the default target
.PHONY: all
all: build
	
.PHONY: build
build:

.PHONY: clean
clean:

.PHONY: clean-objects
clean-objects:
	$(VERBOSE)$(call rm, $(OBJECTS) $(DEPENDS))
	$(call print,Deleted $(PROJECT_NAME) objects and depends)

.PHONY: config
config: $(CC_CONFIG_FILE)

$(CC_CONFIG_FILE): $(WS)/$(PROJECT_CONFIG)
	$(VERBOSE)$(call mkdir, $(dir $@))
	$(VERBOSE)$(call cp, $< $@)
	$(call print,Generated $(PROJECT_NAME) project configuration from $(PROJECT_CONFIG))

.PHONY: config-clean
config-clean:
	$(VERBOSE)$(call rm, $(CC_CONFIG_FILE))
	$(call print,Deleted $(PROJECT_NAME) configuration file)
	
.PHONY: documentation
documentation: html pdf 

.PHONY: documentation-clean
documentation-clean: html-clean pdf-clean
	$(VERBOSE)$(call rmdir, $(DEF_DOX_O))
	$(call print,Deleted all documentation in $(PROJECT_NAME):$(DEF_DOX_O))

.PHONY: pdf
pdf: $(DEF_DOXYFILE)
	$(VERBOSE)$(call echo,GENERATE_LATEX = YES) >> $(DEF_DOXYFILE)	
	$(VERBOSE)$(call doxygen $<)
	$(VERBOSE)$(MAKE) -C $(DEF_DOX_O)/$(DEF_DOX_LATEX_O)
	$(call print,Generated $(PROJECT_NAME) PDF documentation in $(DEF_DOX_O)/$(DEF_DOX_LATEX_O))

.PHONY: html
html: $(DEF_DOXYFILE)
	$(VERBOSE)$(call echo, GENERATE_HTML = YES) >> $(DEF_DOXYFILE)
	$(VERBOSE)$(call doxygen $<)
	$(call print,Generated $(PROJECT_NAME) HTML documentation in $(DEF_DOX_O)/$(DEF_DOX_HTML_O))

.PHONY: clean-lib
clean-lib: clean-objects
	$(VERBOSE)$(call rm, $(PROJECT_LIB))
	$(call print,Deleted $(PROJECT_NAME) library)

.PHONY: clean-elf
clean-elf: clean-lib
	$(VERBOSE)$(call rm, $(PROJECT_ELF))
	$(call print,Deleted $(PROJECT_NAME) executable)

.PHONY: clean-size
clean-size: clean-elf
	$(VERBOSE)$(call rm, $(PROJECT_SIZE))
	$(call print,Deleted $(PROJECT_NAME) executable size report)

.PHONY: clean-flash
clean-flash: clean-elf
	$(VERBOSE)$(call rm, $(PROJECT_FLASH))
	$(call print,Deleted $(PROJECT_NAME) flash binary)

.PHONY: pdf-clean
pdf-clean:
	$(VERBOSE)$(call rmdir, $(DEF_DOX_O)/$(DEF_DOX_LATEX_O))
	$(call print,Deleted $(PROJECT_NAME) PDF documentation)

.PHONY: html-clean
html-clean:
	$(VERBOSE)$(call rmdir, $(DEF_DOX_O)/$(DEF_DOX_HTML_O))
	$(call print,Deleted $(PROJECT_NAME) HTML documentation)

.PHONY: $(DEF_DOXYFILE)
$(DEF_DOXYFILE): $(DEF_DOX_PROJECT) $(DEF_DOX_BASE)
	$(VERBOSE)$(call mkdir, $(dir $@))
	$(VERBOSE)cat $(DEF_DOX_BASE) > $@
	$(VERBOSE)cat $(DEF_DOX_PROJECT) >> $@
	$(VERBOSE)$(call echo,PROJECT_NUMBER = '$(GIT_VERSION)') >> $@
	$(VERBOSE)$(call echo,OUTPUT_DIRECTORY = $(DEF_DOX_O)) >> $@
	$(VERBOSE)$(call echo,HTML_OUTPUT = $(DEF_DOX_HTML_O)) >> $@
	$(VERBOSE)$(call echo,LATEX_OUTPUT = $(DEF_DOX_LATEX_O)) >> $@
	$(call print,Generated $(PROJECT_NAME) doxyfile)
	
.PHONY: help
help:
	@echo "Neon Makefile help for module '$(MOD_NAME)'"
	@echo
	@echo "This module depends on the following modules: $(MOD_DEPS)"
	@echo
	@echo "== BUILD INFORMATION =="
	@echo "Targets:"
	@echo "  all                - Build tests, lib and documentation."
	@echo "  clean              - Clean the build directory."
	@echo "  tests              - Build executable PicoBlocks tests."
	@echo "  lib                - Build static PicoBlocks library."
	@echo "  documentation      - Generate HTML and PDF documentation."
	@echo "  help               - Print this screen."
	@echo
	@echo "Generic arguments:"
	@echo "  V                  - Set verbosity level (default: $(DEF_V)):"
	@echo "                         0 - silent,"
	@echo "                         1 - verbose."
	@echo "  PROFILE            - Make code in (default: $(PROFILE)):"
	@echo "                         release,"
	@echo "                         debug mode."
	@echo
	@echo "Port arguments:"
	@echo "  PLATFORM           - Build for specific platform."
	@echo "                       (default: $(PLATFORM))"
	@echo "  ARCH               - Build for specific CPU architecture."
	@echo "                       (default: $(ARCH))"
	@echo "  MCU                - Build for specific MCU."
	@echo "                       (default: not used)"
	@echo
	@echo "Compiler variables:"
	@echo "  CFLAGS             - Compiler common flags."
	@echo "  COPTIMIZATION_D    - Compiler optimization flags for"
	@echo "                       debug profile."
	@echo "  COPTIMIZATION_R    - Compiler optimization flags for"
	@echo "                       release profile."
	@echo
	@echo "Linker variables:"
	@echo "  LDFLAGS            - Linker common flags."
	@echo "  LDLIBS             - Linker additional libraries."
	@echo
	@echo "Usage example:"
	@echo "  make PLATFORM=$(PLATFORM) ARCH=$(ARCH) CC_FLAGS='-pedantic' V=1"
	@echo

.PHONY: recipe
recipe: config
	$(VERBOSE)echo "PREFIX: " $(PREFIX)
	$(VERBOSE)echo "PROJECT_CONFIG: " $(WS)/$(PROJECT_CONFIG)
	$(VERBOSE)echo "CC_INCLUDES: " $(addprefix $(WS)/, $(CC_INCLUDES))
	$(VERBOSE)echo "CC_FLAGS: " $(CC_FLAGS)
	$(VERBOSE)echo "CC_DEFINES: " $(CC_DEFINES)
	$(VERBOSE)echo "CC_SOURCES: " $(CC_SOURCES)
	$(VERBOSE)echo "LD_FLAGS: " $(LD_FLAGS)
	$(VERBOSE)echo "LD_LIBS: " $(LD_LIBS)

#
# Common library defines/includes/sources
#

# Add common library include folder
CC_INCLUDES += lib/include

# Add generated folder to include paths
CC_INCLUDES += $(PROJECT_DIR)/$(DEF_BUILD_DIR)

endif
