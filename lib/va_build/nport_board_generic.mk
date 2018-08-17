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

# NOTE:
# This is a generic board placeholder. It does not provide any functionality,
# it just creates dummy BSP implementation to satisfy linking.

# Board identifier
BUILD_BOARD := generic

# Additional board description
BUILD_BOARD_DESC := "Generic board"

CC_SOURCES += lib/va_source/nport_board_generic.c
CC_SOURCES += lib/va_source/nport_board_generic_bsp.c
CC_INCLUDES += lib/va_include/nport/board_generic
