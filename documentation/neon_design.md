# Neon v2 Design
*Copyright (C) Real-Time Consulting*

## Contents
1. [Overview](#1-overview)
2. [Time complexity](#2-time-complexity)
3. [Source code organization](#3-source-code-organization)
4. [Neon Core](#4-neon-core)
5. [Neon Portable code](#5-neon-portable-code)

## 1. Overview
### 1.1 Scheduler Policy
Scheduler is using round-robin scheduling algorithm when there are two or more
threads of the same priority ready for execution.

### 1.2. Deterministic
Majority of algorithms used in Neon are belonging to **Constant Time
Complexity** category. Constant Time `O(1)` functions needs fixed amount of
time to execute an algorithm. In other words the execution time of Constant
Time Complexity functions does not depend on number of inputs. For more
information see [time complexity](#2-time-complexity).

### 1.3. Configurable
The Neon provides configuration files (TODO: specify which) which can be
used to tailor the kernel to application needs.

### 1.4. Portable
During the design stage of the kernel a special attention was given to achieve
high portability of the kernel. Some data structures and algorithms are
tailored to exploit new hardware features.

### 1.5. Static object allocation
All objects used in Neon can be statically allocated. There is no need to
use any memory management functionality which makes it very easy to verify the
application.

### 1.6. Unlimited number of threads
Neon allows applications to have any number of threads. The only limiting
factors for the maximum number of threads are the amount of RAM and ROM memory
capacity and required processing time.

### 1.7. Optimized number of priority levels
There are 32 thread priority levels which is optimal value when using 32-bit
CPU architecture. Each word bit represent one level of thread priority. Each
thread has a defined priority. Lowest priority level is 0, while the highest
available level is 31. Multiple threads can share the same priority level. The
priority sorting algorithm has constant time complexity which means it always
executes in the same time period regardles of the levels of priority used.

### 1.8. Error checking
All Neon software is using design methods very similar to approaches of
**contract programming** paradigm for software design. The contract
programming prescribes that Application Programming Interface should have
formal and precise specifications, which extend the ordinary definition of
abstract data types with preconditions and postconditions. These specifications
are referred to as "contracts". The contract for each method will normally
contain the following pieces of information:

- Acceptable and unacceptable input values
- Return values and their meanings
- Error and exception condition values that can occur during the execution
- Side effects
- Preconditions
- Postconditions
- Invariants

The contract validations are done by **assert** macros. They have the
responsibility of informing the programmer when a contract can not be
validated.

### 1.9. Profiling
**NOTE:** This feature is not implemented

## 2. Time complexity
### 2.1 Introduction
In computer science, the time complexity of an algorithm quantifies the amount
of time taken by an algorithm to run as a function of the length of the input.
The time complexity of an algorithm is commonly expressed using **big O**
notation, which excludes coefficients and lower order terms. When expressed
this way, the time complexity is said to be described asymptotically, i.e., as
the input size goes to infinity. For example, if the time required by an
algorithm on all inputs of size `n` is at most ` 5n^3 + 3n`, the asymptotic
time complexity is `O(n^3)`.

Time complexity is commonly estimated by counting the number of elementary
operations performed by the algorithm, where an elementary operation takes a
fixed amount of time to perform. Thus the amount of time taken and the number
of elementary operations performed by the algorithm differ by at most a
constant factor.

Since an algorithm’s performance time may vary with different inputs of the
same size, one commonly uses the worst-case time complexity of an algorithm,
denoted as **T(n)**, which is defined as the maximum amount of time taken on
any input of size `n`. Time complexities are classified by the nature of the
function `T(n)`. For instance, an algorithm with `T(n) = O(n)` is called a
linear time algorithm, and an algorithm with `T(n) = O(2^n)` is said to be an
exponential time algorithm.

**NOTE:**
Worst-case time-complexity `T(n)` indicates the longest running time performed 
by an algorithm given any input of size `n`, and thus this guarantees that the
algorithm finishes on time.

### 2.2 Big O notation
Big O notation describes the limiting behavior of a function when the argument
tends towards a particular value or infinity, usually in terms of simpler
functions and it is used to classify algorithms by how they respond (e.g., in
their processing time or working space requirements) to changes in input size.

### 2.3 Constant time
An algorithm is said to be constant time (also written as `O(1)` time) if the
value of `T(n)` is bounded by a value that does not depend on the size of the
input.

Despite the name *constant time*, the running time does not have to be
independent of the problem size, but an upper bound for the running time has to
be bounded independently of the problem size.

**NOTE:**
Constant time effectively means that there is a constant upper bound to how
long the function will take to run which isn’t affected by any of the input
argument.

### 2.4 Neon time complexity
All Neon functions are using `constant time O(1)` algorithms. This is
especially important for Real Time applications.

## 3. Source code organization
Complete source code is divided into:
- **Core** - Contains the generic functionality of the Neon.
- **Port** - Portable code, depends on the used build target.

## 4. Neon Core
### 4.1. Synchronization
#### 4.1.1. Mutex
#### 4.1.2. Semaphore

## 5. Neon portable code

The portable code is divided into the following layers:
    * Platform layer
    * Architecture layer
    * Microcontroller layer
    * Operating system layer
    * Board layer

### 5.1 Available ports

Ports are identified by board layer name.

### 5.2 Platform layer

Since the Neon needs to support multiple different compilers the platform layer
provides a compiler agnostic interface. The platform layer interface is just a
set of macros which are hiding compiler specific keywords and attributes.
