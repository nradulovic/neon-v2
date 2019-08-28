# Neon v2
*Copyright (C) Real-Time Consulting*

[![pipeline status](https://gitlab.com/rtfw-neon/neon/badges/development/pipeline.svg)](https://gitlab.com/rtfw-neon/neon/commits/development)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/5182921283394e1aa7c8d2cac9a955a5)](https://www.codacy.com/app/nradulovic/neon-v2?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=nradulovic/neon-v2&amp;utm_campaign=Badge_Grade)
[![License: LGPL v3](https://img.shields.io/badge/License-LGPL%20v3-blue.svg)](https://www.gnu.org/licenses/lgpl-3.0)

## Contents
1. [Introduction](#1-introduction)
2. [License](#2-license)
3. [Supported platforms and targets](#3-supported-platforms-and-targets)
4. [Get and build Neon](#4-get-and-build-neon)
5. [Coding standard](#5-coding-standard)
6. [Documentation](#6-documentation)
7. [Support](#7-support)

## 1. Introduction
Neon is a real-time library for deply embedded microcontrollers. For details 
about Neon design refer to [documentation/neon_design.md]. It enforces a 
specific programming paradigm.

The documentation is currently minimal so refer to `project/eclipse`
application examples. For additional examples about particular feature please 
refer to unit-tests `tests` folder.

Neon software provides:
 - multithreaded like execution using cooperative scheduling.
 - dynamic memory allocation. It tries not to replace the standard C library
   malloc, but adds more algorithms for managing RAM memory which are embedded
   friendly.
 - Thin hardware abstraction layer (HAL)
 - Virtual Timers

## 2. License
The software is distributed under open source GNU LESSER GENERAL PUBLIC
LICENSE Version 3. A copy of license file is found in [LGPL-3.0.md].

## 3. Supported platforms and targets
Several different platforms and targets are supported. In order to manage
different configurations, a few build portable layers are available:
 - `platform` - Platform layer abstract the development platfrom being used.
   For example, using the GCC or XC8 compiler is transparent in the code. No
   compiler specific code is in generic part of Neon library.
 - `arch` - Architecture layer abstracts the target CPU core architecture, 
   like x86 or ARMv7-M Cores.
 - `mcu` - Microcontroller layer describes the target MCU features. It will 
   provide details about the available RAM/ROM sizes, available peripherals and
   their limitations etc.
 - `board` - Board layer describes additional peripheral devices attached to
   the MCU pins.
 - `os` - OS layer abstract operating system services.
 
For more specific details about build flags etc, please refer to the file
[documentation/build.md]. Some platforms have different sub-maintainers,
please refer to the file [MAINTAINERS.md] for contact details for various
platforms.

## 4. Get and build Neon

The best way to get the Neon library is to use github or gitlab and then 
checkout a tagged version. All tagged versions live in master branch. If you
want to get the most current version of Neon library then checkout 
`development` branch.

Please see [documentation/build.md] for instructions how to build Neon for
various platforms and targets.

## 5. Coding standard
Information on coding standard used in the project can be found in
[documentation/coding_standard.md]

## 6. Documentation
The documentations consists of multiple ``.md`` files (plain text) and Doxygen
related files. The doxygen tools is used to generate API reference in HTML and
PDF documents. Please, refer to [documentation/documentation.md] for
instructions how to build additional documentation files.

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
