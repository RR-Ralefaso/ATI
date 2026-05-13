#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>

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







    
};