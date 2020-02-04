
Intro
=====

This folder contains files to build various projects using GNU Make tool. GNU
Make is a build automation tool that automatically builds executable programs
and libraries from source code by reading files called Makefiles. 

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


