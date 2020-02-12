# Building project using Make
## Contents

1. [Introduction](#1-introduction)
2. [Supported tools](#2-supported-tools)
3. [Prerequisities](#3-prerequisities)
4. [Generic code building](#4-generic-code-building)
5. [Portable code building](#5-portable-code-building)

## 1. Introduction

This folder contains files to build various projects using GNU Make tool. GNU
Make is a build automation tool that automatically builds executable programs
and libraries from source code by reading files called Makefiles. GNU Make is
common tool found on many Linux distributions.

## 2. Supported tools
### 2.1 x86 / ARM armv-7m on Linux host

| Program       | Minimal version   | Command to check the version |
| ------------- | ----------------- | ---------------------------- |
| GNU C         | 4.9               | gcc --version                |
| GNU make      | 3.81              | make --version               |
| binutils      | 2.20              | ld -v                        |
| coreutils     | 8.25              | cp --version                 |

## 3. Prerequisities

On Ubuntu 16.04/18.04 you will need the following packages:
* make
* doxygen
* doxygen latex tools
* a compiler toolchain

You can get them by typing:

    sudo apt-get install make doxygen doxygen-latex graphviz
    
For ARM Cortex-M processor (armv7-m) install the toolchain:

    sudo apt-get install gcc-arm-none-eabi

## 4. Building an application

To build an application using Neon, go to respective folder of the application
located in 'project/make' folder. The Makefile of the application is already
configured in such a way to find the Neon sources.

To build the application invoke the make command:

    make

The compiled binaries and other output files can be found in 'generated' 
subfolder of the application folder.
    
#### 3.1.3 Making a library
__NOTE__: The following functionallity is yet to be implemented.

To build the library invoke the make command:

    make BOARD=<board_name> PLATFORM=<a_platform> lib
    
This will build the static library in build directory. The compiled binaries
and other output files may be found in 'generated' subfolder of the current 
folder.

#### 3.1.4 Making a package
__NOTE__: The following functionallity is yet to be implemented.

This command allow to easy integrate Neon into an existing project and/or
build system. To create a package containing the produced `.a` library and
necessary header files use:

    make BOARD=<board_name> PLATFORM=<a_platform> package

The package directory is located in `generated/package`. Copy this folder to
your project to use it.

#### 3.1.5 Making the documentation
The command:

    make documentation
    
Will make the API reference documentation in HTML and PDF format in build
directory for this operation you need doxygen, graphviz and doxygen-latex tools
(see prerequisities above). The build directory is 'documentation/generated'.

#### 3.1.6 Making preprocessor files
During debugging and troubleshooting it is beneficial to see the contents of
'.c' and '.S' preprocessed files. To generate preprocessed '.i' files execute
the command:

    make preprocess

This will create '.i' preprocessed files inside 'generated' directory.

## 4. Generic code building
The generic code is located in `lib` folder. To build the generic code a port
needs to be defined (see [Portable code building](#5-portable-code-building)).
Also, the include path should have 

## 5. Portable code building
The portable code is divided into the following layers:
* Platform layer - The source code is located in a subfolder of 
  `variant/platform` folder.
* Architecture layer - The source code is located in a subfolder of 
  `variant/arch` folder.
* Microcontroller layer - The source code is located in a subfolder of 
  `variant/mcu` folder.
* Operating system layer - The source code is located in a subfolder of 
  `variant/os` folder.
* Board layer - The source code is located in a subfolder of 
  `variant/board` folder.

### 5.1 Port examples


|   Port/board name    |  platform  |    arch    |       mcu       |     os     |
| -------------------- | ---------- | ---------- | --------------- | ---------- |
| generic              | gcc        | x86        | generic         | linux      |
| pic18f_monitor       | xc8        | pic18      | pic18f46k40     | none       |
| pic32mx_clicker      | xc32       | pic32      | pic32mx534f064h | none       |
| stm32f103_blue_pill  | gcc        | armv7_m    | stm32f103c8     | none       |


Each portable layer lives in a different folder. The platform layers is defined
in `variant/platform` folder, architecture layers are defined in 
`variant/arch` folder, microcontroller layers are defined in `variant/mcu`
folder, operating system layers are defined in `variant/os` folder and board
layers are defined in `variant/board` folder.

Each portable layer introduces new include path and source folder to the build
system.

Lets say that `generic` port needs to be build. The `generic` port is actually
a Linux application. The `generic` port is defined as:
* platform = `gcc`
* architecture = `x86`
* microcontroller = `generic`
* operating system = `linux`
* board = `generic`
    
In order to build Neon for `generic` port the following needs to be done:
* Add all portable layers include folders to the build system. To do this
  add folders `variant/platform/gcc`, `variant/arch/x86`,
  `variant/mcu/generic`, `variant/os/none` and 
  `variant/board/generic` to include path.
* Add all `.c` source files to list of object that needs to be compiled. 
  The source files are to be found in the following folders: 
  `variant/platform/gcc`, `variant/arch/x86`, `variant/mcu/generic`, 
  `variant/os/none` and `variant/board/generic`. 

Contents
========

This folder contains various project folders which end with '_proj' in its
name and a folder called 'variant'. The 'variant' folder contains additional
makefiles in order to successfullu build the projects.

Each project folder contains a top level Makefile which can be used to build
and or execute the project. Usually the build process goes like this:

    make clean
    make all

For build details please refer to additional project documentation.


