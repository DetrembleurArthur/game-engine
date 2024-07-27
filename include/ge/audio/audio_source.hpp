#ifndef __GE_AUDIO_SOURCE_HPP__
#define __GE_AUDIO_SOURCE_HPP__
#include <al.h>
#include <ge/audio/audio_buffer.hpp>
#include <ge/binding/notify_property.hpp>

namespace ge
{
    class AudioSource
    {
    private:
        ALuint id;
        ALfloat audio_position[3] = {0};
        ALfloat audio_velocity[3] = {0};
        Vec2NotifyProperty position_property;
        NotifyProperty<ALfloat> volume_property;
    public:
        AudioSource(AudioBuffer &buffer, bool spacialization);
        ~AudioSource();
        Vec2NotifyProperty& position();
        Vec2NotifyProperty *position_p();
        NotifyProperty<ALfloat>& volume();
        NotifyProperty<ALfloat> *volume_p();
        bool is_playing();
        void play();
        void stop();
        void loop(bool value=true);
    };
}

#endif
