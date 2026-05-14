run(linux):
---
    sudo apt update
    sudo apt install libsdl2-dev libsdl2-mixer-dev libfftw3-dev build-essential cmake

    cd ATI 
    mkdir -p build && cd build #if it doesnt exist
    cmake ..
    make #build and run




to run manually after installing deps:

    g++ app.cpp src/Equations.cpp -o ati -lSDL2 -lSDL2_mixer -lfftw3 -lm
