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

# Additional OS description
BUILD_HOST_OS_DESC = "Linux"

git_version = $(shell git describe --abbrev=7 --always --dirty --tags 2>/dev/null || echo unknown)
mkdir = mkdir -p $(1)
rm = rm -f $(1)
rmdir = rm -rf $(1)
cp = cp -R $(1) $(2)
echo = echo "$(1)"
doxygen = doxygen
