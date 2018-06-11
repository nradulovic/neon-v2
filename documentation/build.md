# Developer guidelines
## Contents
1. [Introduction](#1-introduction)

---
## 1. Introduction
The build system uses GNU Make and common tools found on many Linux
distributions.

---
## 2. Building methods
### 2.1 Makefile method

The main build method is by invoking the make command from terminal.

#### 2.1.1 Prerequisities

On Ubuntu 16.04 you will need the following packages:
    * make
    * doxygen
    * doxygen latex tools
    * a compiler toolchain

You can get them by typing:

    sudo apt install make doxygen doxygen-latex graphviz
    
For ARM Cortex-M processor install the toolchain:

    sudo apt install gcc-arm-none-eabi

#### 2.1.2 Making an application

To build an Neon application go to respective root folder of the application.
The Makefile of the application should be setup in such a way to find the
root path of Neon libraries.

To build the application invoke the make command:

    make PLATFORM=<a_platform> ARCH=<an_architecture> 

The compiled binaries may be found in 'generated' subfolder of the current
folder.
    
#### 2.1.3 Making a library

__NOTE__: The following functionallity is yet to be implemented.

To build the library invoke the make command:

    make PLATFORM=<a_platform> ARCH=<an_architecture> lib
    
This will build the static library in build directory. The compiled binaries
may be found in 'generated' subfolder of the current folder.

#### 2.1.4 Making a package

__NOTE__: The following functionallity is yet to be implemented.

This command allow to easy integrate Neon into an existing project and/or
build system. To create a package containing the produced `.a` library and
necessary header files use:

    make PLATFORM=<a_platform> ARCH=<an_architecture> package

The package directory is located in `generated/package`. Copy this folder to
your project to use it.

The command:

    make documentation
    
Will make the API reference documentation in HTML and PDF format in build
directory for this operation you need doxygen, graphviz and doxygen-latex tools
(see prerequisities above). The build directory is 'documentation/generated'.


