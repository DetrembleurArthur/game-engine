#ifndef __GE_SOUND_MANAGER_HPP__
#define __GE_SOUND_MANAGER_HPP__
#include <ge/audio/audio_buffer.hpp>
#include <ge/audio/audio_loader.hpp>
#include <ge/audio/audio_source.hpp>
#include <map>
#include <string>

namespace ge
{
    class SoundManager
    {
    private:
        std::map<std::string, AudioBuffer *> sounds;
        AudioSource *music=nullptr;
    public:
        SoundManager();
        ~SoundManager();
        AudioBuffer& load(const std::string& filename, const std::string& name);
        AudioBuffer& get(const std::string& name);
        AudioSource *as_music(const std::string& name);
        AudioSource *get_music();
    };
}

#endif
