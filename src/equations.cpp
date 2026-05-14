/*
@author : Rothang Ralph Ralefaso
@email : rrralefaso@outloook.com
@github : github.com/RR-Ralefaso
@date : 2026
*/

#include "Equations.hpp"
#include <cmath>
#include <fstream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace ATI
{

    Audiomapper::Audiomapper() : sdlInitialized(false)
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
            return;
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            return;
        sdlInitialized = true;
    }

    Audiomapper::~Audiomapper()
    {
        if (sdlInitialized)
        {
            Mix_CloseAudio();
            SDL_Quit();
        }
    }

    int Audiomapper::GetWidth()
    {
        SDL_DisplayMode dm;
        return (SDL_GetCurrentDisplayMode(0, &dm) == 0) ? dm.w : 1920;
    }

    int Audiomapper::GetHeight()
    {
        SDL_DisplayMode dm;
        return (SDL_GetCurrentDisplayMode(0, &dm) == 0) ? dm.h : 1080;
    }

    double Audiomapper::GetLength(const std::string &filepath)
    {
        Mix_Music *music = Mix_LoadMUS(filepath.c_str());
        if (!music)
            return 0.0;
        double duration = Mix_MusicDuration(music);
        Mix_FreeMusic(music);
        return duration;
    }

    std::vector<Audiomapper::FrequencyPoint> Audiomapper::GetFrequencyMap(const std::string &filepath)
    {
        std::vector<FrequencyPoint> freqMap;
        SDL_AudioSpec wavSpec;
        Uint32 wavLength;
        Uint8 *wavBuffer;

        if (SDL_LoadWAV(filepath.c_str(), &wavSpec, &wavBuffer, &wavLength) == nullptr)
            return freqMap;

        int sampleCount = wavLength / 2;
        int16_t *samples = (int16_t *)wavBuffer;
        double sampleRate = wavSpec.freq;

        const int N = 2048;
        const int HOP_SIZE = 512; // Increased overlap for more detail
        double *in = (double *)fftw_malloc(sizeof(double) * N);
        fftw_complex *out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);
        fftw_plan p = fftw_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);

        for (int i = 0; i + N < sampleCount; i += HOP_SIZE)
        {
            double currentTime = i / sampleRate;
            for (int j = 0; j < N; j++)
            {
                // Hann Window to reduce noise
                double window = 0.5 * (1.0 - cos(2.0 * M_PI * j / (N - 1)));
                in[j] = (samples[i + j] / 32768.0) * window;
            }
            fftw_execute(p);

            for (int k = 0; k < N / 2; k++)
            {
                float mag = std::sqrt(out[k][0] * out[k][0] + out[k][1] * out[k][1]);
                // Lower threshold to capture more quiet frequencies
                if (mag > 0.005f)
                {
                    freqMap.push_back({currentTime, (int)(k * sampleRate / N), mag});
                }
            }
        }

        fftw_destroy_plan(p);
        fftw_free(in);
        fftw_free(out);
        SDL_FreeWAV(wavBuffer);
        return freqMap;
    }

    void Audiomapper::CreateSpectrogramPNG(const std::vector<FrequencyPoint> &freqMap, int imgWidth, int imgHeight, const std::string &outputFilename)
    {
        if (freqMap.empty())
            return;

        std::vector<uint8_t> buffer(imgWidth * imgHeight * 3, 0);
        double maxTime = 0, maxFreq = 8000.0; // Zooming into the audible range

        for (const auto &pt : freqMap)
            if (pt.timestamp > maxTime)
                maxTime = pt.timestamp;

        for (const auto &pt : freqMap)
        {
            int x = (int)((pt.timestamp / maxTime) * (imgWidth - 1));
            int y = (imgHeight - 1) - (int)((std::min((double)pt.frequencyHz, maxFreq) / maxFreq) * (imgHeight - 1));

            if (x >= 0 && x < imgWidth && y >= 0 && y < imgHeight)
            {
                // Logarithmic intensity (dB scaling)
                float db = 20.0f * std::log10(pt.magnitude + 1e-6f);
                int normalized = static_cast<int>((db + 60.0f) * (255.0f / 60.0f));
                uint8_t v = std::clamp(normalized, 0, 255);

                int pos = (y * imgWidth + x) * 3;

                // "Inferno" Palette (Black -> Blue -> Red -> Yellow -> White)
                buffer[pos] = std::clamp(v * 2, 0, 255);           // Red channel
                buffer[pos + 1] = std::clamp(v - 50, 0, 255);      // Green channel
                buffer[pos + 2] = std::clamp(255 - v * 2, 0, 255); // Blue channel
            }
        }

        stbi_write_png(outputFilename.c_str(), imgWidth, imgHeight, 3, buffer.data(), imgWidth * 3);
    }

} // namespace ATI