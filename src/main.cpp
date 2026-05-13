#include <iostream>
#include <cstdlib>
#include "Equations.hpp" //the equations ima use
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

    return EXIT_SUCCESS;
}