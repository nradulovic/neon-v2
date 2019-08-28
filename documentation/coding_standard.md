# Coding standard
## Contents
1. [Naming convetions](#1-naming-convetions)
2. [Abbreviations](#2-abbreviations)

## 1. Naming convetions
### 1.1. General
1. All objects are using underscore `_` as word delimiter.
2. All objects are using *lowercase* style with the exceptions of macros which
  are using *uppercase* style.
3. Objects are following the following naming format: 
   `[namespace_]object[_method[_attribute]][_class]`
   - Field **namespace** is mandatory only for public objects. Local object
     shall not have namespace prefix.
   - Field **object** defines the object name.
   - Field **method** is optional and describes the object method.
   - Field **attribute** is optional and describes a particular object
     attribute.
   - Field **class** specifies the method class. For details see [method
     classes](#1-4-method-classes).

Lets consider this function name `ntask_get_name`. Decoding goes like this:
- Namespace of this function is *n* which means it belongs to Neon API 
  namespace.
- Object is *task*.
- Method is *get*, get an attribute value.
- Attribute is called *name*.
- No class specified, which means a normal API object.

### 1.2. Neon objects naming
All objects declared in Application Programming Interface (API) which are
public are following this naming style:
- Functions, structures, unions and typedefs and macros have no specific prefix.
- Global variables have namespace prefix `global`.

All objects declared in Application Programming Interface (API) which are
private are following this naming style:
- Functions, structures, unions and typedefs have object name prefix `p_`.
- Macros have object name prefix `P_`.
- Global variables have name prefix `pglobal_`.

### 1.3. Name examples

The following are a few examples:

* ntask_get_name:
    * `n` is the Neon API namespace prefix.
    * `task` is regular object name.
    * `get` is object method.
    * `name` is some attribute of the object on which the method 
      operates on.
* nglobal_list:
    * `n` is the Neon API namespace prefix.
    * `global_` is object prefix which denotes that the object is of
      global scope.
    * `list` is the name of the object.
* np_testsuite_run:
    * `n` is the Neon API namespace prefix.
    * `p_` is object prefix which denotes that the object is private. 
      This object shall not be used by callers code.
    * `testsuite` is the name of the object.
    * `run` is object method.

### 1.4. Method classes
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
| task                      | tsk  |
| timer                     | tmr  |
| queue                     | q    |
| virtual                   | v    |

[documentation/interrupts.md]: documentation/interrupts.md
