/*
@author : Rothang Ralph Ralefaso
@email : rrralefaso@outloook.com
@github : github.com/RR-Ralefaso
@date : 2026
*/

#ifndef EQUATIONS_HPP
#define EQUATIONS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <fftw3.h>

namespace ATI
{

    class Audiomapper
    {
    public:
        struct FrequencyPoint
        {
            double timestamp;
            int frequencyHz;
            float magnitude;
        };

        Audiomapper();
        ~Audiomapper();

        int GetWidth();
        int GetHeight();
        double GetLength(const std::string &filepath);

        std::vector<FrequencyPoint> GetFrequencyMap(const std::string &filepath);
        void CreateSpectrogramPNG(const std::vector<FrequencyPoint> &freqMap, int imgWidth, int imgHeight, const std::string &outputFilename);

    private:
        bool sdlInitialized;
    };

} // namespace ATI

#endif