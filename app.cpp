#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cctype>
#include "src/Equations.hpp" // The equations you'll use

using namespace ATI;

/*
@author : Rothang Ralph Ralefaso
@email : rrralefaso@outloook.com
@github : github.com/RR-Ralefaso
@date : 2026
*/

// Function to execute system commands
int ExecuteCommands(const char *command)
{
    std::cout << "Executing Command... \n"
              << std::endl;
    int returnCode = std::system(command);

    if (returnCode == 0)
    {
        std::cout << "Command executed successfully." << std::endl;
        return EXIT_SUCCESS;
    }
    else
    {
        std::cerr << "Command failed with code: " << returnCode << std::endl;
        return EXIT_FAILURE;
    }
}

// Function to convert string to lowercase
std::string toLowerCase(std::string data)
{
    std::transform(data.begin(), data.end(), data.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    return data;
}

int main()
{
    std::cout << "This program is used to take in audio (file/live) and convert it into frequencies \n"
              << "then create an image based on each frequency. \n\n"
              << "Using the TOTAL DETAIL equation:\n"
              << "    Total pixels = (L * Ps) * H \n"
              << "       -> L  = length of song (seconds)\n"
              << "       -> Ps = Pixels per second (your stretch factor)\n"
              << "       -> H  = Height\n\n"
              << "       -> Ps = total width of screen (pixels) / total length of song (seconds)\n\n"
              << std::endl;

    Audiomapper mapper;

    // Compile external dependencies if necessary
    const char *command = "g++ -c src/Equations.cpp -o build/Equations.o $(sdl2-config --cflags) -lfftw3";
    if (ExecuteCommands(command) == EXIT_FAILURE)
    {
        std::cerr << "Failed to create the object file. Check your compiler and paths." << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Created build file successfully\n"
              << std::endl;

    // User input for mode selection
    std::cout << "Would you like to upload a file or live recording:\n"
              << std::endl;
    std::string response;

    do
    {
        std::cout << "   for Live input [L]\n   for uploading input [U]" << std::endl;
        if (!std::getline(std::cin, response))
            return EXIT_FAILURE;
        response = toLowerCase(response);
    } while (response.empty() || (response != "l" && response != "u"));

    /*============================== actual logic ================================*/

    std::string filepath;

    switch (response[0])
    {
    case 'l':
        std::cout << "Live recording mode selected (Implementation pending...)" << std::endl;
        break;

    case 'u':
    {
        // 1. Get file location
        do
        {
            std::cout << "\nWhat is the location of the audio file? (Use absolute path): " << std::endl;
            std::getline(std::cin, filepath);
        } while (filepath.empty());

        mapper.filepath = filepath;

        // 2. Extract metadata and process frequencies
        // Note: Storing values in variables to avoid repeated heavy function calls
        double length = mapper.GetLength(filepath);
        double Ps = mapper.GetPixelsPerSecond(filepath);
        int width = mapper.GetWidth();
        int height = mapper.GetHeight();
        double totalPixels = mapper.GetTotalPixels(filepath);

        // Getting the Frequency Map (Assuming Fm is a vector of doubles or similar)
        auto Fm = mapper.GetFrequencyMap(filepath);

        std::cout << "\nFile Info:\n"
                  << " - Length: " << length << "s\n"
                  << " - Width: " << width << "px\n"
                  << " - Height: " << height << "px\n"
                  << " - Total Pixels: " << totalPixels << "\n"
                  << std::endl;

        // 3. Save location
        std::string savepath;
        do
        {
            std::cout << "Where would you like to save the output image? (Absolute path): " << std::endl;
            std::getline(std::cin, savepath);
        } while (savepath.empty());

        // 4. Generate the result
        mapper.CreateSpectrogram(Fm, width, height, savepath);
        std::cout << "Spectrogram saved to: " << savepath << std::endl;
    }
    break;

    default:
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}