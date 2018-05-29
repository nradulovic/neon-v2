# Developer guidelines
## Contents
1. [Introduction](#1-introduction)

---
## 1. Introduction
Each real time kernel port consists of two group of files that contain the core
kernel components (`core` directory) and are common to every port, and one or
more files that are specific to a particular microcontroller and or compiler.

* The source directory `core` contains the file that is common to every port:
`pblocks.c`. The kernel is contained within this file.
* The portable directory `ports` contains the files that are specific to a
particular microcontroller and or compiler.
* The `core` directory contains the real time kernel header files.

---
## 2. Building methods
### 2.1 Makefile method

The main build method is by invoking the make command from terminal. This
build will produce a static library file which you can use in your project.

#### 2.1.1 Prerequisities

On Ubuntu 16.04 you will need the following packages:
    * make
    * doxygen
    * doxygen latex tools
    * a compiler toolchain

You can get them by typing:

    sudo apt install make doxygen doxygen-latex graphviz
    
For ARM Cortex-M processor install:

    sudo apt install gcc-arm-none-eabi

#### 2.1.2 Making a library

To build the library invoke the make command:

    make PLATFORM=$(PLATFORM) ARCH=$(ARCH) lib
    
This will build the static library in build directory. The name of library
corresponds to build platform/architecture. For example, the library for an ARM
cortex-m3 MCU using the GCC toolchain would be named: 
`pblocks-gcc-arm-none-eabi-cortex-m3.a`. Note that in final build step the
Makefile will copy the library to `pblocks.a` file.

#### 2.1.3 Making a package

This command allow to easy integrate Neon into an existing project and/or
build system. To create a package containing the produced `.a` library and
necessary header files use:

    make PLATFORM=$(PLATFORM) ARCH=$(ARCH) pack

The package directory is located in `build/package`. Now copy this folder to
your project to use it.

The command:

    make documentation
    
Will make the API reference documentation in HTML and PDF format in build
directory for this operation you need doxygen, graphviz and doxygen-latex tools
(see prerequisities above).


