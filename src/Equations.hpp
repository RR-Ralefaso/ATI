#ifndef EQUATIONS_HPP
#define EQUATIONS_HPP

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

namespace ATI{
    class Audiomapper{

        public:

            std::string filepath; //path to file
            //functions declarations
            int GetWidth();
            int GetHeight();
            
            double GetLength(const std::string &filepath);
            double GetPixelsPerSecond(std::string &filepath);
            double GetTotalPixels(const std::string &filepath);

        
    };
} // namespace for ATI
#endif