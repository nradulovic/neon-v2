#
# Neon
# Copyright (C)  2017  Nenad Radulovic
#
# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
# more details.
#
# You should have received a copy of the GNU General Public License along with
# this program. If not, see <http://www.gnu.org/licenses/>.
#

# NOTE:
# This is a generic MCU placeholder. It does not provide any functionality,
# it just creates dummy BSP implementation to satisfy linking.

# MCU identifier
BUILD_MCU := generic

# Additional MCU description
BUILD_MCU_DESC := "Generic MCU"

# Additional MCU information
BUILD_MCU_FAM := generic
BUILD_MCU_ATTR :=

CC_SOURCES += lib/va_source/nport/nport_mcu_generic.c
CC_INCLUDES += lib/va_include/nport/mcu_generic
