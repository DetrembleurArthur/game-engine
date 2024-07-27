#include "ge/core/sound_manager.hpp"
#include <ge/utils/log.hpp>

ge::SoundManager::SoundManager()
{
}

ge::SoundManager::~SoundManager()
{
    for(auto it = sounds.begin(); it != sounds.end(); it++)
    {
        if(it->second)
        {
            delete it->second;
            log("delete " + it->first + " sound", LogLevels::AUDIO);
        }
    }
}

ge::AudioBuffer &ge::SoundManager::load(const std::string &filename, const std::string &name)
{
    AudioInfos&& audio = AudioLoader::load(filename);
    AudioBuffer *buffer = new AudioBuffer();
    buffer->fill_with_wav(audio);
    sounds[name] = buffer;
    return *buffer;
}

ge::AudioBuffer &ge::SoundManager::get(const std::string &name)
{
    return *sounds[name];
}

ge::AudioSource *ge::SoundManager::as_music(const std::string &name)
{
    if(music)
    {
        delete music;
        music = nullptr;
    }
    music = new ge::AudioSource(get(name), false);
    music->loop();
    return music;
}

ge::AudioSource *ge::SoundManager::get_music()
{
    return music;
}

