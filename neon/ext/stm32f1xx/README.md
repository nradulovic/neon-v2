
---
# 1. Introduction
This folder contains necessary minimal sources to setup Neon to use STM Cube 
F1 software library.

---
# 2. Setup
Extract the contents of archives downloaded from ``www.st.com`` into this 
folder. The .ZIP archive will usually contain a folder named 
``STM32Cube_FW_F1_Vx.y.z`` where ``x``, ``y`` and ``z`` are library
version number. The Eclipse project was setup in such a way to ignore the
library version so you can freelly update the library without expecting any
build errors (assuming that ST does not change it's API in a significant 
fasion). After extraction rename the folder to ``STM32Cube_FW_F1``.
