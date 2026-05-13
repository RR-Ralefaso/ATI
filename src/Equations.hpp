#ifndef EQUATIONS_HPP
#define EQUATIONS_HPP

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

namespace ATI{
    class Audiomapper{

        std::string filepath; //path to file

        //functions declarations
        int GetWidth();
        int GetHeight();
        double GetLength(const std::string &filepath);
        double GetPixelsPerSecond();
    };
} // namespace for ATI
#endif