#include "ge/audio/audio_listener.hpp"

ALfloat ge::AudioListener::audio_position[3] = {0};
ALfloat ge::AudioListener::audio_velocity[3] = {0};
ALfloat ge::AudioListener::audio_orientation[6] = {0.0, 0.0, -1.0, 0.0, 1.0, 0.0};
ge::Vec2NotifyProperty ge::AudioListener::position_property;
ge::NotifyProperty<ALfloat> ge::AudioListener::volume_property;


void ge::AudioListener::init()
{
    position_property.on_change([](glm::vec2 pos) {
            audio_position[0] = pos.x;
            audio_position[1] = pos.y;
            audio_position[2] = 0;
            alListenerfv(AL_POSITION, audio_position);
        });
    volume_property.on_change([](ALfloat volume) {
        alListenerf(AL_GAIN, volume);
    });
    alListenerfv(AL_VELOCITY, audio_velocity);
    alListenerfv(AL_ORIENTATION, audio_orientation);
}

ge::Vec2NotifyProperty &ge::AudioListener::position()
{
    return position_property;
}

ge::Vec2NotifyProperty *ge::AudioListener::position_p()
{
    return &position_property;
}

ge::NotifyProperty<ALfloat> &ge::AudioListener::volume()
{
    return volume_property;
}

ge::NotifyProperty<ALfloat> *ge::AudioListener::volume_p()
{
    return &volume_property;
}

