
nbitarray - Neon Bit Array
==========================

The Neon Bit Array represents a data structure that holds 256 bits. Each bit
is represented by an address. Address space is linear and goes from 0 to 255.
Each bit can be set and reset. The msbs() (Most Significant Bit Set) function
will return the most significant set bit in the array.


Possible configurations
=======================

Insertion algorithms used with various scheduling techniques and priority 
groups and levels.


Ready queue algorithm overview:

| groups | 8   | 8   | 16  | 16  | 32  | 64  | 256 |
| level  | 8   | 32  | 16  | 32  | 32  | 64  | 256 |
+--------+-----+-----+-----+-----+-----+-----+-----+
| RR     | FB  | SB  | FB  | SB  | FB  |     |     |
| PRIO   | DB  |     | DB  |     | DB  | DB  | DB  |

Wait queue algorithm overview:

| groups | 8   | 8   | 16  | 16  | 32  | 64  | 256 |
| level  | 8   | 32  | 16  | 32  | 32  | 64  | 256 |
+--------+-----+-----+-----+-----+-----+-----+-----+
| RR     | SQ  | SQ  | SQ  | SQ  | SQ  |     |     |
| PRIO   | DB  |     | DB  |     | DB  | SQ  | SQ  |


| scheme | levels | groups | rdy q  | wait q |
+--------+--------+--------+--------+--------+
| RR     | 8      | 8      | FB     | SQ     |
| RR     | 8      | 32     | SB     | SQ     |
| RR     | 16     | 16     | FB     | SQ     |
| RR     | 16     | 32     | SB     | SQ     |
| RR     | 32     | 32     | FB     | SQ     |
| PRIO   | 8      | 8      | DB     | SQ     |
| PRIO   | 16     | 16     | DB     | DB     |
| PRIO   | 32     | 32     | DB     | DB     |
| PRIO   | 64     | 64     | DB     | SQ     |
| PRIO   | 256    | 256    | DB     | SQ     |

Maximum number of tasks:

- RR: Unlimited number of tasks
- PRIO: Equals to priority levels.

Legend:
 - RR - Round Robin with Priority scheduling
 - PRIO - Priority scheduling
 - SB - Sorted bitmap queue algorithm
 - FB - FIFO bitmap queue algorithm
 - DB - Direct bitmap queue algorithm
 - SQ - Sorted queue queue algorithm


Round Robin with Pririty scheduling
-----------------------------------

When Round Robin scheduling is enabled only up to 32 priority levels exist in
the system.
