# Developer guidelines
## Contents
1. [Introduction](#1-introduction)
2. [Vision](#2-vision)
3. [Coding rules](#3-coding-rules)

---
## 1. Introduction
This document is for developers who want to modify PicoBlocks source.

---
## 2. Vision
Some of key principles used in development of PicoBlocks:
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

[wiki overchoice]: https://en.wikipedia.org/wiki/Overchoice
