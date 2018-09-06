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

ifneq ("$(PROJECT_CONFIG)","")
$(info Using Application config: $(PROJECT_CONFIG))
CC_DEFINES += NEON_APP_CONFIG=\"$(PROJECT_CONFIG)\"
endif

endif
