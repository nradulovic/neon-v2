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
ifndef LIB_BUILD_NCONFIG_MK
LIB_BUILD_NCONFIG_MK=1

# Dependencies
include $(WS)/lib/build/common.mk
include $(WS)/lib/build/nport.mk

# Generate version information
CC_DEFINES += NCONFIG_GIT_VERSION=\"$(call git_version)\"

# Generate custom configuration
#
# If a custom (project) configuration has been configured then a special macro
# will be defined so the configuration file can be included by generic
# configuration header. See nconfig_default.h file for more information.
ifneq ($(PROJECT_CONFIG),)
CC_DEFINES += NCONFIG_PROJECT_CONFIG=1
endif

endif
