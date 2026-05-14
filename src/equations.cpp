#include "Equations.hpp"
#include <cmath>

/*
@author : Rothang Ralph Ralefaso
@email : rrralefaso@outloook.com
@github : github.com/RR-Ralefaso
@date : 2026
*/


class AudioMapper{


    public:

        


        //path of the file
        std::string filepath;
        int Height, Width; //height and width
        double LengthOfSong, PixelsPerSecond, TotalPixels;

        // AudioMapper()
        // {
        //     this->filepath = "";
        //     this->Height = 0;
        //     this->Width = 0;
        //     this->PixelsPerSecond = 0;
        //     this->TotalPixels = 0;
        //     this->LengthOfSong = 0;
        // }




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
            return (double)EXIT_FAILURE;
        }

        // Get length in seconds
        double duration = Mix_MusicDuration(music);

        // Clean up
        Mix_FreeMusic(music);
        Mix_CloseAudio();

        return duration;
    }

    // euqation : Ps = total width of screen (pixels) / total length of song (seconds)
    double GetPixelsPerSecond(std::string &filepath)
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

    //equation : Tp = (L*Ps)*H
    double GetTotalPixels(std::string &filepath){
        double Length = (double)GetLength(filepath);
        double width  = (double)GetWidth();
        double height = (double)GetHeight();
        if (Length <= 0.0 || width<=0 || height<= 0.0 )
        {
            std::cerr << "invalid" << std::endl;
            return (double)EXIT_FAILURE;
        }
        return Length * height * width;
    }


    struct FrequencyPoint
    {
        double timestamp , frequency;
        float magnitude;

    };

    std::vector<FrequencyPoint> GetFrequencyMap(const std::string &filepath)
    {
        std::vector<FrequencyPoint> freqMap;

        // 1. Load Audio Data using SDL
        SDL_AudioSpec wavSpec;
        Uint32 wavLength;
        Uint8 *wavBuffer;

        if (SDL_LoadWAV(filepath.c_str(), &wavSpec, &wavBuffer, &wavLength) == nullptr)
        {
            std::cerr << "Could not open audio file: " << SDL_GetError() << std::endl;
            return freqMap;
        }

        // Logic for 16-bit Mono (common for analysis)
        int sampleCount = wavLength / 2;
        int16_t *samples = (int16_t *)wavBuffer;
        double sampleRate = wavSpec.freq;

        // 2. FFTW Setup
        const int N = 2048;        // Window Size
        const int HOP_SIZE = 1024; // Overlap

        // FFTW requires specific memory allocation for speed (SIMD alignment)
        double *in = (double *)fftw_malloc(sizeof(double) * N);
        fftw_complex *out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);

        // Create a 'plan' (FFTW_MEASURE is slow once, FFTW_ESTIMATE is fast)
        fftw_plan p = fftw_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);

        // 3. Sliding Window Analysis
        for (int i = 0; i + N < sampleCount; i += HOP_SIZE)
        {
            double currentTime = i / sampleRate;

            // Prepare Input: Apply Hann Window and Normalize
            for (int j = 0; j < N; j++)
            {
                double window = 0.5 * (1.0 - cos(2.0 * M_PI * j / (N - 1)));
                in[j] = (samples[i + j] / 32768.0) * window;
            }

            // Execute FFT
            fftw_execute(p);

            // 4. Extract Frequency Data
            // We only look at N/2 because the second half is a mirror image
            for (int k = 0; k < N / 2; k++)
            {
                // Magnitude = sqrt(real^2 + imag^2)
                double real = out[k][0];
                double imag = out[k][1];
                float magnitude = std::sqrt(real * real + imag * imag);

                // Convert to dB (optional but recommended for music)
                // float db = 20.0f * std::log10(magnitude + 1e-6);

                if (magnitude > 0.05f)
                { // Threshold to ignore silence/noise
                    FrequencyPoint pt;
                    pt.timestamp = currentTime;
                    pt.frequency = static_cast<int>(k * sampleRate / N);
                    pt.magnitude = magnitude;
                    freqMap.push_back(pt);
                }
            }
        }

        // 5. Cleanup
        fftw_destroy_plan(p);
        fftw_free(in);
        fftw_free(out);
        SDL_FreeWAV(wavBuffer);

        return freqMap;
    }

}; //end of class (helps with brackets)