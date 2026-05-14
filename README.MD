compiling Equations:
--------------------
    g++ -c src/Equations.cpp -o build/Equations.o $(sdl2-config --cflags)
        
Compiling app :
----------------
    g++ -c app.cpp -o build/main.o $(sdl2-config --cflags)

Linking them :
--------------
    g++ build/main.o build/Equations.o -o ATI $(sdl2-config --libs) -lSDL2_mixer
