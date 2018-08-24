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

# Include guard
ifndef LIB_BUILD_NLIB_MK
LIB_BUILD_NLIB_MK=1

NCONFIG_GIT_VERSION := "$(shell git describe --abbrev=7 --always --dirty --tags 2>/dev/null || echo unknown)"

# Add common library include folder
CC_INCLUDES += lib/include

# Add generated folder include folder
CC_INCLUDES += $(PROJECT_DIR)/$(DEF_BUILD_DIR)

# Common defines for the library
CC_DEFINES += NCONFIG_GIT_VERSION=\"$(NCONFIG_GIT_VERSION)\"

# Library header configuration
CC_CONFIG_FILE = $(DEF_BUILD_DIR)/neon_config.h

.PHONY: config
config: $(CC_CONFIG_FILE)

$(CC_CONFIG_FILE): $(WS)/$(PROJECT_CONFIG)
	$(PRINT) Project configuration file "$(WS)/$(PROJECT_CONFIG)"
	$(VERBOSE)mkdir -p $(dir $@)
	$(VERBOSE)cp $(WS)/$(PROJECT_CONFIG) $@

.PHONY: config-clean
config-clean:
	$(VERBOSE)rm -f $(CC_CONFIG_FILE)

endif
