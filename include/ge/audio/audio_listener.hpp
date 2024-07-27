#ifndef __GE_AUDIO_LISTENER_HPP__
#define __GE_AUDIO_LISTENER_HPP__
#include <al.h>
#include <ge/binding/notify_property.hpp>

namespace ge
{
    class AudioListener
    {
    private:
        static ALfloat audio_position[3];
        static ALfloat audio_velocity[3];
        static ALfloat audio_orientation[6];
        static Vec2NotifyProperty position_property;
        static NotifyProperty<ALfloat> volume_property;
    public:
        static void init();
        static Vec2NotifyProperty& position();
        static Vec2NotifyProperty *position_p();
        static NotifyProperty<ALfloat>& volume();
        static NotifyProperty<ALfloat> *volume_p();
    };
}

#endif
