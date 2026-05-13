#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class AudioMapper{

    //gets the screen width
    int GetWidth(){
        SDL_DisplayMode dm;
        if (SDL_GetCurrentDisplayMode(0, &dm) == 0) // SDL_GetCurrentDisplayMode returns 0 on success
        {
            return dm.w;
        }
        return EXIT_FAILURE;
    }

    //get screen height
    int GetHeight(){
        SDL_DisplayMode dm;

        if(SDL_GetCurrentDisplayMode(0,&dm)==0){
            return dm.h;

        }
        return EXIT_FAILURE;
    }


    //get the song length in length
    int GetLength(){
        
    }

    // euqation : Ps = total width of screen (pixels) / total length of song (seconds)
    int GetPixelsPerSecond(){
        if (GetWidth() == 0)
        {
            std::cerr << "width of screen detected to be 0" << std::endl; //output will be 0
            return EXIT_FAILURE;
        }
        if (GetLength()==0){ //divison by 0
            std::cerr << "song length is 0";
            exit;
        }
        return (GetWidth() / GetLength());
    }
};