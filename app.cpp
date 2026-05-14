/*
@author : Rothang Ralph Ralefaso
@email : rrralefaso@outloook.com
@github : github.com/RR-Ralefaso
@date : 2026
*/

#include <iostream>
#include <string>
#include <algorithm>
#include "src/Equations.hpp"

int main()
{
    ATI::Audiomapper mapper;
    std::string response;

    std::cout << "--- Audio To Image Mapper ---\n";
    std::cout << "Author: Rothang Ralph Ralefaso\n\n";

    std::cout << "Would you like to upload a file [U] or live recording [L]? ";
    std::getline(std::cin, response);

    if (!response.empty() && std::tolower(response[0]) == 'u')
    {
        std::string filepath, savepath;
        std::cout << "Enter .wav file path: ";
        std::getline(std::cin, filepath);

        std::cout << "Processing frequency map...\n";
        auto Fm = mapper.GetFrequencyMap(filepath);

        if (Fm.empty())
        {
            std::cerr << "Error: Could not process audio file.\n";
            return 1;
        }

        int w = mapper.GetWidth();
        int h = mapper.GetHeight();

        std::cout << "Enter save path (e.g., result.ppm): ";
        std::getline(std::cin, savepath);

        mapper.CreateSpectrogram(Fm, w, h, savepath);
        std::cout << "Spectrogram successfully created at " << w << "x" << h << ".\n";
    }
    else
    {
        std::cout << "Live mode is currently under development.\n";
    }

    return 0;
}