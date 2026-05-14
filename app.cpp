#include <iostream>
#include <cstdlib>
#include "src/Equations.hpp" //the equations ima use
using namespace ATI;
#include <algorithm> 
#include <cctype>   

/*
@author : Rothang Ralph Ralefaso
@email : rrralefaso@outloook.com
@github : github.com/RR-Ralefaso
@date : 2026

*/


//executing commands function
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





//tolowercase function
std::string toLowerCase(std::string data)
{
    std::transform(data.begin(), data.end(), data.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    return data;
}



int main()
{
    std::cout << "this program is used to take in audio (file/live) and convert it into frquencies then create an image based of each frequency. \n\n"
              << "using the TOTAL DETAIL equation :\n    Total pixels = (L * Ps) * H \n"
              << "       -> L  = length of song (seconds)\n"
              << "       -> Ps = Pixels per second (yours tretch factor)\n"
              << "       -> H  = Height"
              <<"\n\n"
              <<"        ->Ps = total width of screen (pixels) / total length of song (seconds)\n\n"
              << std::endl;

    Audiomapper mapper;

    //executing commands to build the equations
    const char *command = "g++ -c src/Equations.cpp -o build/Equations.o $(sdl2-config --cflags) -lfftw3";
    if(ExecuteCommands(command) == EXIT_FAILURE){
        std::cerr << "failed to create the object file\n" << std::endl;
        exit;
    }
    std::cout << "created build file successfully\n"
              << std::endl;



    // starting off by asking user if they want live audio or not
    std::cout << "would you like to upload a file or live recording:\n"<< std::endl;
    std::string response;
    //taking in user inout with validation
    do{
        std::cout << "   for Live input [L]\n   for uploading input [U]" << std::endl;
        getline(std::cin, response);
        response = toLowerCase(response); 
    } while (response.empty() || (response != "l" && response != "u"));

    


    /*==============================actual logic================================*/

    std::string filepath;

    switch (response[0])
    {
        case 'l':
                break;

        case 'u':
        //get file location ensure it isnt empty
            do
            {
                std::cout << "\n\nwhat is the location of the audio file (use absolute path)\n"
                          << std::endl;
                getline(std::cin, filepath);
            } while (filepath.empty());
            mapper.filepath = filepath;
            

            break;
        default :
            exit;
    }

    return EXIT_SUCCESS;
}