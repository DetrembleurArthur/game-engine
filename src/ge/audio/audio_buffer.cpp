#include "ge/audio/audio_buffer.hpp"
#include <al.h>
#include <ge/utils/log.hpp>

ge::AudioBuffer::AudioBuffer()
{
    alGenBuffers(1, &id);
    int error = alGetError();
    if(error != AL_NO_ERROR)
    {
        log("error at audio buffer creation: " + std::to_string(error), LogLevels::ERROR);
    }
    else
    {
        log("buffer created", LogLevels::AUDIO);
    }
}

ge::AudioBuffer::~AudioBuffer()
{
    alDeleteBuffers(1, &id);
    log("buffer destroyed", LogLevels::AUDIO);
}

void ge::AudioBuffer::fill_with_wav(AudioInfos &audio)
{
    alBufferData(id, audio.format, audio.data.data(), audio.size, audio.sample_rate);
    int error = alGetError();
    if(error != AL_NO_ERROR)
    {
        log("error at audio buffer creation: " + std::to_string(error), LogLevels::ERROR);
    }
    else
    {
        log("buffer filled", LogLevels::AUDIO);
    }
}

ALuint ge::AudioBuffer::get_id()
{
    return id;
}
