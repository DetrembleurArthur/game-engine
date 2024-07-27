#ifndef __GE_AUDIO_LOADER_HPP__
#define __GE_AUDIO_LOADER_HPP__
#include <cstdint>
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <al.h>

namespace ge
{
    struct AudioInfos
    {
        std::vector<short> data;
        std::uint8_t channels;
        std::int32_t sample_rate;
        std::uint8_t bits_per_sample;
        ALsizei size;
        ALenum format;
    };

    class AudioLoader
    {
    private:

    public:
        static AudioInfos load(const std::string& filename);
    };
}

#endif
