/*
@author : Rothang Ralph Ralefaso
@email : rrralefaso@outloook.com
@github : github.com/RR-Ralefaso
@date : 2026
*/

#include <iostream>
#include <string>
#include "src/Equations.hpp"

int main()
{
    ATI::Audiomapper mapper;
    std::string filepath, savepath;

    std::cout << "--- Professional Audio-to-PNG Engine ---\n";
    std::cout << "Author: Rothang Ralph Ralefaso\n\n";

    std::cout << "Enter path to WAV file: ";
    std::getline(std::cin, filepath);

    std::cout << "Performing Fast Fourier Transform (FFT)...\n";
    auto freqData = mapper.GetFrequencyMap(filepath);

    if (freqData.empty())
    {
        std::cerr << "Error: File could not be processed. Ensure it is a valid WAV.\n";
        return 1;
    }

    int w = mapper.GetWidth();
    int h = mapper.GetHeight();

    std::cout << "Enter output filename (e.g., viz.png): ";
    std::getline(std::cin, savepath);

    std::cout << "Generating high-detail spectrogram...\n";
    mapper.CreateSpectrogramPNG(freqData, w, h, savepath);

    std::cout << "Done! Saved to " << savepath << " at " << w << "x" << h << "\n";

    return 0;
}