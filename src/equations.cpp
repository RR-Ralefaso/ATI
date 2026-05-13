#include "Equations.hpp"
#include <cmath>

class AudioMapper{


    public:
        //path of the file
        std::string filepath;

        // gets the screen width
        int GetWidth()
        {
            SDL_DisplayMode dm;
            if (SDL_GetCurrentDisplayMode(0, &dm) == 0) // SDL_GetCurrentDisplayMode returns 0 on success
            {
                return dm.w;
            }
            return EXIT_FAILURE;
        }

    //get screen height
    int GetHeight(){
        SDL_DisplayMode dm;

        if(SDL_GetCurrentDisplayMode(0,&dm)==0){
            return dm.h;

        }
        return EXIT_FAILURE;
    }


    //get the song length in length
    double GetLength(const std::string &filepath)
    {
        // Initialize SDL_mixer (Frequency, Format, Channels, Chunksize)
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            std::cerr << "SDL_mixer could not initialize! Error: " << Mix_GetError() << std::endl;
            return -1.0;
        }

        Mix_Music *music = Mix_LoadMUS(filepath.c_str());
        if (!music)
        {
            std::cerr << "Failed to load music! Error: " << Mix_GetError() << std::endl;
            Mix_CloseAudio();
            return -1.0;
        }

        // Get length in seconds
        double duration = Mix_MusicDuration(music);

        // Clean up
        Mix_FreeMusic(music);
        Mix_CloseAudio();

        return duration;
    }

    // euqation : Ps = total width of screen (pixels) / total length of song (seconds)
    double GetPixelsPerSecond()
    {
        int width = GetWidth();

        if (width <= 0)
        {
            std::cerr << "Error: Width of screen is 0 or negative." << std::endl;
            return 0.0;
        }

        // Call GetLength once and store it to save CPU/Disk usage
        double songLength = GetLength(filepath);

        if (songLength <= 0)
        {
            std::cerr << "Error: Song length is 0 or file could not be read." << std::endl;
            // Return 0 instead of 'exit' to keep the program running
            return 0.0;
        }

        // Equation: Ps = total width / total length
        return static_cast<double>(width) / songLength;
    }


};