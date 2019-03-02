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
BUILD_HOST_OS_DESC = "Windows"

git_version = $(shell git describe --abbrev=7 --always --dirty --tags 2> nul || echo unknown)
mkdir = mkdir $(subst /,\,$(1)) > nul 2>&1 || (exit 0)
rm = $(wordlist 2,65535,$(foreach FILE,$(subst /,\,$(1)),& del $(FILE) > nul 2>&1)) || (exit 0)
rmdir = rmdir $(subst /,\,$(1)) > nul 2>&1 || (exit 0)
cp = copy $(subst /,\,$(1)) $(subst /,\,$(2)) > nul 2>&1 || (exit 0)
echo = echo $(1)
doxygen = doxygen $(subst /,\,$(1))