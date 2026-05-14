/*
@author : Rothang Ralph Ralefaso
@email : rrralefaso@outloook.com
@github : github.com/RR-Ralefaso
@date : 2026
*/

#include "Equations.hpp"
#include <cmath>
#include <fstream>
#include <algorithm>

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

    double Audiomapper::GetPixelsPerSecond(const std::string &filepath)
    {
        double len = GetLength(filepath);
        return (len > 0) ? static_cast<double>(GetWidth()) / len : 0.0;
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
        const int HOP_SIZE = 1024;
        double *in = (double *)fftw_malloc(sizeof(double) * N);
        fftw_complex *out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);
        fftw_plan p = fftw_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);

        for (int i = 0; i + N < sampleCount; i += HOP_SIZE)
        {
            double currentTime = i / sampleRate;
            for (int j = 0; j < N; j++)
            {
                // Apply Hann Window
                double window = 0.5 * (1.0 - cos(2.0 * M_PI * j / (N - 1)));
                in[j] = (samples[i + j] / 32768.0) * window;
            }

            fftw_execute(p);

            for (int k = 0; k < N / 2; k++)
            {
                float mag = std::sqrt(out[k][0] * out[k][0] + out[k][1] * out[k][1]);
                if (mag > 0.02f)
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

    void Audiomapper::CreateSpectrogram(const std::vector<FrequencyPoint> &freqMap, int imgWidth, int imgHeight, const std::string &outputFilename)
    {
        if (freqMap.empty())
            return;

        std::vector<uint8_t> buffer(imgWidth * imgHeight * 3, 0);
        double maxTime = 0, maxFreq = 10000.0;
        float maxMag = 0;

        for (const auto &pt : freqMap)
        {
            if (pt.timestamp > maxTime)
                maxTime = pt.timestamp;
            if (pt.magnitude > maxMag)
                maxMag = pt.magnitude;
        }

        for (const auto &pt : freqMap)
        {
            int x = (int)((pt.timestamp / maxTime) * (imgWidth - 1));
            int y = (imgHeight - 1) - (int)((std::min((double)pt.frequencyHz, maxFreq) / maxFreq) * (imgHeight - 1));

            if (x >= 0 && x < imgWidth && y >= 0 && y < imgHeight)
            {
                uint8_t intensity = (uint8_t)((pt.magnitude / maxMag) * 255);
                int pos = (y * imgWidth + x) * 3;
                // Grayscale with a blue tint
                buffer[pos] = intensity / 2;
                buffer[pos + 1] = intensity;
                buffer[pos + 2] = intensity;
            }
        }

        std::ofstream outFile(outputFilename, std::ios::binary);
        outFile << "P6\n"
                << imgWidth << " " << imgHeight << "\n255\n";
        outFile.write((char *)buffer.data(), buffer.size());
    }

} // namespace ATI