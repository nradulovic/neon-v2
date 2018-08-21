# Developer guidelines
## Contents
1. [Introduction](#1-introduction)

---
## 1. Introduction
The build system uses GNU Make and common tools found on many Linux
distributions.

---
## 2. Supported tools

### 2.1 x86 / ARM armv-7m on Linux host

| Program       | Minimal version   | Command to check the version |
| ------------- | ----------------- | ---------------------------- |
| GNU C         | 4.9               | gcc --version                |
| GNU make      | 3.81              | make --version               |
| binutils      | 2.20              | ld -v                        |
| coreutils     | 8.25              | cp --version                 |

---
## 3. Building methods
### 3.1 Makefile method

The main build method is by invoking the make command from terminal.

#### 3.1.1 Prerequisities

On Ubuntu 16.04/18.04 you will need the following packages:
    * make
    * doxygen
    * doxygen latex tools
    * a compiler toolchain

You can get them by typing:

    sudo apt install make doxygen doxygen-latex graphviz
    
For ARM Cortex-M processor (armv7-m) install the toolchain:

    sudo apt install gcc-arm-none-eabi

#### 2.1.2 Making an application

To build an Neon application go to respective root folder of the applications
located in 'apps/' folder. The Makefile of the application should be setup in
such a way to find the root path of Neon.

To build the application invoke the make command:

    make BOARD=<board_name> PLATFORM=<a_platform> 

The compiled binaries and other output files may be found in 'generated' 
subfolder of the current folder.
    
#### 2.1.3 Making a library

__NOTE__: The following functionallity is yet to be implemented.

To build the library invoke the make command:

    make BOARD=<board_name> PLATFORM=<a_platform> lib
    
This will build the static library in build directory. The compiled binaries
and other output files may be found in 'generated' subfolder of the current 
folder.

#### 2.1.4 Making a package

__NOTE__: The following functionallity is yet to be implemented.

This command allow to easy integrate Neon into an existing project and/or
build system. To create a package containing the produced `.a` library and
necessary header files use:

    make BOARD=<board_name> PLATFORM=<a_platform> package

The package directory is located in `generated/package`. Copy this folder to
your project to use it.

The command:

    make documentation
    
Will make the API reference documentation in HTML and PDF format in build
directory for this operation you need doxygen, graphviz and doxygen-latex tools
(see prerequisities above). The build directory is 'documentation/generated'.


