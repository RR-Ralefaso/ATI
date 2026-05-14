run(linux):
---
    sudo apt update
    make run

compile without running :
------------------------
    make

to start over:
--------------
    make clean


to run manually after installing deps:
--------------------------------------
    g++ app.cpp src/Equations.cpp -o ati -lSDL2 -lSDL2_mixer -lfftw3 -lm
