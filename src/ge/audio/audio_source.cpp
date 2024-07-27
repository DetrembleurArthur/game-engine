#include "ge/audio/audio_source.hpp"
#include <ge/utils/log.hpp>

// Fonction pour obtenir la position d'une source
glm::vec3 get_source_position(ALuint source_id) {
    ALfloat position[3];
    alGetSourcefv(source_id, AL_POSITION, position);
    return glm::vec3(position[0], position[1], position[2]);
}

// Fonction pour obtenir la position du listener
glm::vec3 get_listener_position() {
    ALfloat position[3];
    alGetListenerfv(AL_POSITION, position);
    return glm::vec3(position[0], position[1], position[2]);
}

// Fonction pour calculer la distance entre la source et le listener
float calculate_distance_between_source_and_listener(ALuint source_id) {
    glm::vec3 source_position = get_source_position(source_id);
    glm::vec3 listener_position = get_listener_position();
    return glm::length(source_position - listener_position);
}

ge::AudioSource::AudioSource(AudioBuffer &buffer, bool spacialization)
{
    alGenSources(1, &id);
    int error = alGetError();
    if(error != AL_NO_ERROR)
    {
        log("error at audio source creation: " + std::to_string(error), LogLevels::ERROR);
    }
    else
    {
        log("source created", LogLevels::AUDIO);
    }
    alSourcei(id, AL_BUFFER, buffer.get_id());
    if(error != AL_NO_ERROR)
    {
        log("error at audio source & buffer binding: " + std::to_string(error), LogLevels::ERROR);
    }
    else
    {
        log("source bind to buffer", LogLevels::AUDIO);
        position_property.on_change([this](glm::vec2 pos) {
            audio_position[0] = pos.x;
            audio_position[1] = pos.y;
            audio_position[2] = 0;
            alSourcefv(id, AL_POSITION, audio_position);
            std::cout << calculate_distance_between_source_and_listener(id) << std::endl;
        });
        volume_property.on_change([this](ALfloat volume) {
            alSourcef(id, AL_GAIN, volume);
        });
        volume_property.set(1.0);
        alSourcefv(id, AL_VELOCITY, audio_velocity);
        alSourcef(id, AL_REFERENCE_DISTANCE, 100.0f);  // Distance de référence
        alSourcef(id, AL_MAX_DISTANCE, 3000.0f);       // Distance maximale
        alSourcef(id, AL_ROLLOFF_FACTOR, spacialization ? 1.00f : 0.0f);      // Facteur de rolloff
        alSourcei(id, AL_SOURCE_RELATIVE, AL_TRUE);
    }
}

ge::AudioSource::~AudioSource()
{
    alSourceStop(id);
    alDeleteSources(1, &id);
    log("source destroyed", LogLevels::AUDIO);
}

ge::Vec2NotifyProperty &ge::AudioSource::position()
{
    return position_property;
}

ge::Vec2NotifyProperty *ge::AudioSource::position_p()
{
    return &position_property;
}

ge::NotifyProperty<ALfloat> &ge::AudioSource::volume()
{
    return volume_property;
}

ge::NotifyProperty<ALfloat> *ge::AudioSource::volume_p()
{
    return &volume_property;
}

bool ge::AudioSource::is_playing()
{
    ALint state;
    alGetSourcei(id, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
}

void ge::AudioSource::play()
{
    alSourcePlay(id);
}

void ge::AudioSource::stop()
{
    alSourceStop(id);
}

void ge::AudioSource::loop(bool value)
{
    alSourcei(id, AL_LOOPING, value);
}
