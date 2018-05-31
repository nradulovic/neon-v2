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

$(call check_defined, WS, WS is relative path to nbase project)

# Documentation defaults
DEF_DOX_O        = documentation/generated
DEF_DOX_HTML_O   = html
DEF_DOX_LATEX_O  = latex
DEF_DOX_PROJECT  = documentation/$(MOD_NAME)_doxyfile
DEF_DOX_BASE     = $(BUILD_SRC)/../documentation/base_doxyfile
DEF_DOXYFILE	 = $(DEF_DOX_O)/doxyfile

# Builder helper variables
OBJECTS          = $(patsubst %.c,$(BUILD_DIR)/%.o,$(CC_SOURCES))
OBJECTS         += $(patsubst %.s,$(BUILD_DIR)/%.o,$(AS_SOURCES))
DEPENDS          = $(patsubst %.o,%.d,$(OBJECTS))

# Create possible targets
PROJECT_NAME   ?= undefined
PROJECT_CONFIG ?= $(WS)/lib/include/configs/default_config.h
PROJECT_ELF     = $(BUILD_DIR)/$(PROJECT_NAME).elf
PROJECT_LIB     = $(BUILD_DIR)/$(PROJECT_NAME).a
PROJECT_FLASH   = $(BUILD_DIR)/$(PROJECT_NAME).hex
PROJECT_SIZE    = $(BUILD_DIR)/$(PROJECT_NAME).siz

# Common build variables
BUILD_SRC        = $(WS)/build
BUILD_DIR        = generated

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

# This is the default target
.PHONY: all
all:

.PHONY: clean
clean:

.PHONY: clean-objects
clean-objects: 
	$(VERBOSE)rm -f $(OBJECTS) $(DEPENDS)

.PHONY: documentation
documentation: html pdf 

.PHONY: documentation-clean
documentation-clean: html-clean pdf-clean
	$(VERBOSE)rm -rf $(DEF_DOX_O)
	$(PRINT) "Documentation cleaned up"

.PHONY: html
html: $(DEF_DOXYFILE)
	@echo "GENERATE_HTML = YES" >> $(DEF_DOXYFILE)
	$(PRINT) "Generating HTML documentation..."
	$(VERBOSE)doxygen $< >/dev/null
	@echo
	$(PRINT) "HTML generated in $(DEF_DOX_O)/$(DEF_DOX_HTML_O)"

.PHONY: html-clean
html-clean:
	$(PRINT) "Cleaning HTML documentation..."
	$(VERBOSE)rm -rf $(DEF_DOX_O)/$(DEF_DOX_HTML_O)

.PHONY: pdf
pdf: $(DEF_DOXYFILE)
	@echo "GENERATE_LATEX = YES" >> $(DEF_DOXYFILE)	
	$(PRINT) "Generating PDF documentation..."
	$(VERBOSE)doxygen $< >/dev/null
	$(VERBOSE)$(MAKE) -C $(DEF_DOX_O)/$(DEF_DOX_LATEX_O)
	@echo
	$(PRINT) "PDF generated in $(DEF_DOX_O)/$(DEF_DOX_LATEX_O)"

.PHONY: pdf-clean
pdf-clean:
	$(PRINT) "Cleaning PDF documentation..."
	$(VERBOSE)rm -rf $(DEF_DOX_O)/$(DEF_DOX_LATEX_O)

.PHONY: $(DEF_DOXYFILE)
$(DEF_DOXYFILE): $(DEF_DOX_PROJECT) $(DEF_DOX_BASE)
	$(PRINT) "Generating Doxyfile..."
	@mkdir -p $(dir $@)
	@cat $(DEF_DOX_BASE) > $@
	@cat $(DEF_DOX_PROJECT) >> $@
	@echo "PROJECT_NUMBER = '$(GIT_VERSION)'" >> $@
	@echo "OUTPUT_DIRECTORY = $(DEF_DOX_O)" >> $@
	@echo "HTML_OUTPUT = $(DEF_DOX_HTML_O)" >> $@
	@echo "LATEX_OUTPUT = $(DEF_DOX_LATEX_O)" >> $@

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

.PHONY: cc_include_paths
cc_include_paths:
	$(foreach i,$(CC_INCLUDES),$(info $(WS)/$(i)))

.PHONY: c_sources
cc_sources:
	$(foreach i,$(CC_SOURCES),$(info $(WS)/$(i)))

.PHONY: c_flags
cc_flags:
	$(foreach i,$(CC_FLAGS),$(info $(i)))

