#include <iostream>
#include <cstdlib>
#include "src/Equations.hpp" //the equations ima use
using namespace ATI;

int main()
{
    std::cout << "this program is used to take in audio (file/live) and convert it into frquencies then create an image based of each frequency. \n\n"
              << "using the TOTAL DETAIL equation :\n    Total pixels = (L * Ps) * H \n"
              << "       -> L  = length of song (seconds)\n"
              << "       -> Ps = Pixels per second (yours tretch factor)\n"
              << "       -> H  = Height"
              <<"\n\n"
              <<"        ->Ps = total width of screen (pixels) / total length of song (seconds)"
              << std::endl;

    Audiomapper mapper;

    // starting off by asking user if they want live audio or not
    std::cout << "would you like to upload a file or live recording:\n"<< std::endl;
    std::string response;
    //taking in user inout with validation
    do{
        std::cout << "   for Live input [L]\n   for uploading input [u]" << std::endl;
        getline(std::cin, response);
    } while (response.empty());

    return EXIT_SUCCESS;
}