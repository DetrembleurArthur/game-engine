#ifndef __GE_AUDIO_HPP__
#define __GE_AUDIO_HPP__
#include <alc.h>

namespace ge
{
    class Audio
    {
    private:
        static ALCdevice *device;
        static ALCcontext *context;
    public:
        static void init();
        static void destroy();
    };
}

#endif

