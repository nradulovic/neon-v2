# Developer guidelines

## Contents

1. [Introduction](#1-introduction)
2. [Vision](#2-vision)
3. [Coding rules](#3-coding-rules)

---
## 1. Introduction
This document is for developers who want to modify or contribute to  Neon source.

---
## 2. Vision
Some of key principles used in development of Neon:
- Do not offer a plenthora of source code configuration options. Offering to
  many options may confuse the user and bring in necessary burden on them to
  think about configuration (see [wiki overchoice]). Always choose and hardcode
  the options which will be of benefit to most of users.
- Always choose the simplest implementation. Use the KISS principle.
- The software is optimized to run on 32-bit microcontrollers. It's time to let
  go of using 8, 16, 24-bit microcontrollers. Today, we have so many 32-bit
  options available.

---
## 3. Coding rules

### 3.1 Fixed or predefined values

Never code a fixed value directly in code. Always use a macro for this job:

```c
#define SOME_LIMIT_CONDITION 23

uint32_t configurable_size_array[SOME_LIMIT_CONDITION];
```

### 3.2 Comments

The Rob Pike article "Notes on programming in C" section about comments is
spot on:

```
A delicate matter, requiring taste and judgement. I tend to err on the side of
eliminating comments, for several reasons. First, if the code is clear, and
uses good type names and variable names, it should explain itself.  Second, 
comments aren't checked by the compiler, so there is no guarantee they're 
right, especially after the code is modified.  A misleading comment can be very
confusing. Third, the issue of typography: comments clutter code.

But I do comment sometimes. Almost exclusively, I use them as an introduction
to what follows. Examples: explaining the use of global variables and types 
(the one thing I always comment in large programs); as an introduction to an
unusual or critical procedure; or to mark off sections of a large computation.
```

[wiki overchoice]: https://en.wikipedia.org/wiki/Overchoice
