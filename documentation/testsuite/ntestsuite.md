
Test Doubles Variations
=======================

+---------------+-------------------------------------------------------------+
| Name          | Variation                                                   |
+---------------+-------------------------------------------------------------+
| Test dummy    | Keeps the linker from rejecting your build. A dummy is a    |
|               | simple stub that is never called. It is provided to satisfy |
|               | the complier, linker, or runtime dependency.                |
+---------------+-------------------------------------------------------------+
| Test stub     | Returns some val ue, as directed by the current test case.  |
+---------------+-------------------------------------------------------------+
| Test spy      | Captures the parameters passed from the CUT so the test can |
|               | verify that the correct parameters have been passed to the  |
|               | CUT. The spy can also feed return val ues to the CUT just   |
|               | like a test stub.                                           |
+---------------+-------------------------------------------------------------+
| Mock Object   | Verifies the functions called, the call order, and the      |
|               | parameters passed from the CUT to the DOC. It also is       |
|               | programmed to return specific values to the CUT. The mock   |
|               | object is usually dealing with a situation where multiple   |
|               | calls are made to it, and each call and response are        |
|               | potentially different.                                      |
+---------------+-------------------------------------------------------------+
| Fake Object   | Provides a partial implementation for the replaced          |
|               | component. The fake usually has a  simplified               |
|               | implementationwhen compared to the replaced implementation. |
+---------------+-------------------------------------------------------------+
| Exploding     | Causes the test to fail if it is called.                    |
| Fake          |                                                             |
+---------------+-------------------------------------------------------------+

Abbreviations
=============

CUT - Code Under Test
DOC - Depend On Components

