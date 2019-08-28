# Building Neon
## Contents

1. [Introduction](#1-introduction)
2. [Supported tools](#2-supported-tools)
   2.1. [x86 / ARM armv-7m on Linux host](#2-1-x86-arm-armv-7m-on-linux-host)
3. [Build methods](#3-build-methods)
    3.1. [Makefile method](#3-1-makefile-method)
         3.1.1. [Prerequisities](#3-1-1-prerequisities)
         3.1.2. [Making an application](#3-1-2-making-an-application)
         3.1.3. [Making a library](#3-1-3-making-a-library)
         3.1.4. [Making a package](#3-1-4-making-a-package)
         3.1.5. [Making the documentation](#3-1-5-making-the-documentation)
         3.1.6. [Making preprocessor files](#3-1-6-making-preprocessor-files)
4. [Generic code building](#4-generic-code-building)
5. [Portable code building](#5-portable-code-building)
   5.1. [Port examples](#5-1-port-examples)
6. [Eclipse projects](#6-eclipse-projects)   
   6.1. [Project test_proj](#6-1-project-test_proj)


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
## 3. Build methods
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

#### 3.1.2 Making an application

To build an Neon application go to respective root folder of the applications
located in 'apps/' folder. The Makefile of the application should be setup in
such a way to find the root path of Neon.

To build the application invoke the make command:

    make BOARD=<board_name> PLATFORM=<a_platform> 

The compiled binaries and other output files may be found in 'generated' 
subfolder of the current folder.
    
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


## 6. Eclipse projects

Eclipse projects are located in `project/eclipse` folder.

### 6.1 Project test_proj

The project is intended to execute unit-tests on various platforms. The folowing
project profiles are defined:
    * Base - only `lib` folder is included in the build. This profile is not
      able to produce any kind of binary. It is used only to define basic
      settings for core library.  
    * Base-generic - the `lib` folder and generic port is built. This profile
      is not able to produce any kind of binary either. It is used only to
      define settings for core library and generic port.
    * Base-test-generic - compiler `lib`, generic port, testsuite and tests.
      The linker will be able to link the project and generate a binary. Since
      no macro is defined no actual tests will be executed.
    * test-generic-nport - execute nport tests using generic port.
    * test-generic-nbits - execute nbits tests using generic port.
    * test-generic-nlist-sll - execute nlist_sll tests using generic port.