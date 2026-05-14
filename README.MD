run(linux):
---
    sudo apt update && sudo apt install -y libsdl2-dev libsdl2-mixer-dev libfftw3-dev cmake build-essential
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
