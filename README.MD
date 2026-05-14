compiling Equations:
--------------------
    g++ main.cpp Equations.cpp -o Equations $(sdl2-config --cflags --libs) -lSDL2_mixer
        
Compiling main :
----------------
    g++ Main.cpp -o main