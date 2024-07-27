#include "ge/audio/audio.hpp"
#include <ge/utils/log.hpp>
#include <al.h>

ALCdevice *ge::Audio::device=nullptr;
ALCcontext *ge::Audio::context=nullptr;

void ge::Audio::init()
{
    log("init audio", LogLevels::AUDIO);
    device = alcOpenDevice(nullptr);
    if(device)
    {
        log("device opened", LogLevels::AUDIO);
        context = alcCreateContext(device, nullptr);
        if(context)
        {
            alcMakeContextCurrent(context);
            log("context created", LogLevels::AUDIO);
        }
        else
        {
            alcCloseDevice(device);
            device = nullptr;
        }
    }
    int error;
    if ((error = alGetError()) != AL_NO_ERROR)
    {
        log("audio error code: " + std::to_string(error), LogLevels::ERROR);
    } 
    else
    {
        log("audio initialized", LogLevels::AUDIO);
    }
}

void ge::Audio::destroy()
{
    ALCcontext *context = alcGetCurrentContext();
    ALCdevice *device = alcGetContextsDevice(context);
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    log("context destroyed", LogLevels::AUDIO);
    alcCloseDevice(device); 
    log("device destroyed", LogLevels::AUDIO);
    log("audio destroyed", LogLevels::AUDIO);
}
