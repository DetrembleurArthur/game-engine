#ifndef __GE_SOUND_COMPONENT_HPP__
#define __GE_SOUND_COMPONENT_HPP__
#include <ge/entity/components/component.hpp>
#include <ge/audio/audio_source.hpp>
#include <map>

namespace ge
{
    class SoundComponent : public Component
    {
    private:
        std::map<std::string, AudioSource *> audio_sources;
    public:
        using Component::Component;
        ~SoundComponent();
        void add(const std::string& name, AudioBuffer& audio, bool spacialization=true);
        void del(const std::string& name);
        AudioSource *get(const std::string& name);
        void play(const std::string& name, bool if_terminated=false);
    };
}

#endif
