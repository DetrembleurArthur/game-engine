#ifndef __GE_AUDIO_BUFFER_HPP__
#define __GE_AUDIO_BUFFER_HPP__
#include <al.h>
#include <ge/audio/audio_loader.hpp>

namespace ge
{
    class AudioBuffer
    {
    private:
        ALuint id;
    public:
        AudioBuffer();
        ~AudioBuffer();
        void fill_with_wav(AudioInfos& audio);
        ALuint get_id();
    };
}

#endif

