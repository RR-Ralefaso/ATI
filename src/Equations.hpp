#ifndef EQUATIONS_HPP
#define EQUATIONS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// SDL and Audio Libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <fftw3.h>

/*
@author : Rothang Ralph Ralefaso
@email : rrralefaso@outloook.com
@github : github.com/RR-Ralefaso
@date : 2026
*/

namespace ATI
{

    class Audiomapper
    {
    public:
        // Struct must be defined before the function signature using it
        struct FrequencyPoint
        {
            double timestamp;
            int frequencyHz;
            float magnitude;
        };

        // Path to audio file
        std::string filepath;
        std::string outputFilename;
        
        // --- Screen & Dimension Helpers ---
        int GetWidth();
        int GetHeight();
        int imgWidth, imgHeight;

        // --- Audio Metadata ---
        double GetLength(const std::string &filepath);

        // --- Mapping Calculations ---
        double GetPixelsPerSecond(const std::string &filepath);
        double GetTotalPixels(const std::string &filepath);

        // --- Core Frequency Analysis ---
        /**
         * Analyzes the audio using FFTW3 and returns a vector
         * of magnitudes mapped to time and frequency.
         */
        std::vector<FrequencyPoint> GetFrequencyMap(const std::string &filepath);


        //creating image
        void CreateSpectrogram(const std::vector<FrequencyPoint> &freqMap, int imgWidth, int imgHeight, const std::string &outputFilename);
        // private:
        //     // Adding a private helper for internal calculations is often useful
        //     // e.g., double sampleRate = 44100.0;
    };


} // namespace ATI

#endif // EQUATIONS_HPP