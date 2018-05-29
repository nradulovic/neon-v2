# Neon
## Contents
1. [Introduction](#1-introduction)
2. [License](#2-license)
3. [Platforms supported](#3-platforms-supported)
4. [Get and build Neon](#4-get-and-build-neon)
5. [Coding standard](#5-coding-standard)
6. [Documentation](#6-documentation)
7. [Support](#7-support)

## 1. Introduction
Neon is a real-time kernel for deply embedded microcontrollers. For
details about Neon design refer to [documentation/neon_design.md].

---
## 2. License
The software is distributed under open source GNU LESSER GENERAL PUBLIC LICENSE
Version 3. A copy of license file is found in [lgpl-3.0.md].

---
## 3. Platforms supported
Several platforms are supported. In order to manage different configurations, a
few flags have been introduced:
 - `PLATFORM` - describes the development platfrom being used. For example,
   GCC or ARM CC compiler.
 - `ARCH` - describes the target MCU CPU core architecture, like x86 or 
   ARMv7-M Cores.
 - `MCU` - describes the targer MCU as a whole unit. It will provide details
   about the available RAM/ROM sizes, peripheral configuration etc.
 - `BOARD` - it will even describe additional peripheral devices attached to
   the MCU pins.

For more specific details about build flags etc, please refer to the file
[documentation/build.md]. Some platforms have different sub-maintainers,
please refer to the file [MAINTAINERS.md] for contact details for various
platforms.

---
## 4. Get and build Neon
Neon source consist of a ``.c`` files located in `lib/source` and
`lib/va_source`. The header ``.h`` files are located in `lib/include` and
`lib/va_include` directories. The include paths are managed by build system
according to arguments given for selected platform. Please see 
[documentation/build.md] for instructions how to run Neon on various devices.

---
## 5. Coding standard
Information on coding standard used in the project can be found in
[documentation/coding_standard.md]

---
## 6. Documentation
The documentations consists of multiple ``.md`` files (plain text) and Doxygen
related files. The doxygen tools is used to generate API reference in HTML and
PDF documents. Please, refer to [documentation/documentation.md] for build
instructions.

---
## 7. Support
If you've found an error, please file an issue at [issues].

Patches are encouraged, and may be submitted by [forking] this project and
submitting a pull request through GitHub. Please see [CONTRIBUTING.md] for
more details.

[documentation/build.md]: documentation/build.md
[documentation/documentation.md]: documentation/documentation.md
[documentation/coding_standard.md]: documentation/coding_standard.md
[documentation/neon_design.md]: documentation/neon_design.md
[documentation/build.md]: documentation/build.md
[CONTRIBUTING.md]: CONTRIBUTING.md
[MAINTAINERS.md]: MAINTAINERS.md
[lgpl-3.0.md]: lgpl-3.0.md
[issues]: https://github.com/nradulovic/neon-v2/issues/new
[forking]: https://github.com/nradulovic/neon-v2/fork
