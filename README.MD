compiling Equations:
--------------------
    g++ -c src/Equations.cpp -o Equations.o $(sdl2-config --cflags)
        
Compiling main :
----------------
    g++ Main.cpp -o main