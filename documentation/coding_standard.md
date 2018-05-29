# Coding standard
## Contents
1. [Naming convetions](#1-naming-convetions)
1.1. [General](#11-general)
1.2. [Neon Core API](#12-neon-core-api)
1.3. [Neon Port API](#13-neon-port-api)
1.4. [Objects](#14-objects)
1.5. [Method classes](#15-method-classes)
2. [Abbreviations](#2-abbreviations)

---
## 1. Naming convetions
### 1.1. General
1. All objects are using underscore `_` as word delimiter.
2. All objects are using *lowercase* style with the exceptions of macros which
  are using *uppercase* style.
3. Objects are following the following naming format: 
   `[namespace_]object[_method[_attribute]][_class]`
   - Field **namespace** is mandatory only for public objects. Local object
     shall not have namespace prefix.
   - Field **object** defines the object.
   - Field **method** is optional and describes the object method.
   - Field **attribute** is optional and describes a particular object
     attribute.
   - Field **class** specifies the method class. For details see method
     classes.

Lets consider this function `pb_thread_get_name`. Decoding goes like this:
- Namespace of this function is *pb* which means it belongs to
  Neon API namespace.
- Object is *thread*.
- Method is *get*, get an attribute value.
- Attribute is called *name*.
- No class specified, which means a normal API call.

### 1.2. Neon Core API
All public objects declared in Application Programming Interface (API) are
following this naming style:
- Functions, structures, unions and typedefs have namespace prefix `pb_`.
- Macros have namespace prefix `PB_`.
- Global variables have namespace prefix `gpb_`.

### 1.3. Neon Port API
All Neon Port Interface objects are are following this naming style:
- Functions, structures, unions and typedefs have namespace prefix `pbport_`.
- Macros have namespace prefix `PBPORT_`.
- Global variables have namespace prefix `gpbport_`.

### 1.4. Objects
The following groups are defined in Neon API and ports:
- `kernel` - Kernel services.
- `thread` - Thread management.
- `mutex` - Mutex management.
- `semaphore` - Semaphore management.
- `timer` - Timer management, depending on the namespace it may be a virtual
   timer (provided by Neon main API) or hardware timer (provided by
   Neon port).
- `memory_pool` - Memory Pool management.
- `message_queue` - Message Queue management.
- `cpu` - Used in Neon Port, CPU core.

### 1.5. Method classes
- When no class is specified the method belongs to normal API call.
- `_i` - I class - Regular interrupts must be locked before invoking the
  function. To manage the interrupts please refer to
  [documentation/interrupts.md].

---
## 2. Abbreviations
Some of the words which are very frequently being used in the source code are
abbreviated using the table presented below:

| Word | Abbreviation |
|------|--------------|
| interrupt                 | intr |
| interrupt service routine | isr  |
| interrupt request         | irq  |
| priority                  | prio |
| thread                    | thd  |
| timer                     | tmr  |
| queue                     | q    |
| virtual                   | v    |

[documentation/interrupts.md]: documentation/interrupts.md
