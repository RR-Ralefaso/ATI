compiling Equations:
--------------------
    g++ -c src/Equations.cpp -o build/Equations.o $(sdl2-config --cflags) -lfftw3
        
Compiling app :
----------------
    g++ -c app.cpp -o build/app.o $(sdl2-config --cflags)

Linking them :
--------------
    g++ build/app.o build/Equations.o -o ATI $(sdl2-config --libs) -lSDL2_mixer -lfftw3
