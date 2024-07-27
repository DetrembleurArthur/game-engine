#include "ge/entity/components/sound_component.hpp"
#include <ge/entity/components/shape_properties_component.hpp>
#include <ge/entity/game_object.hpp>


ge::SoundComponent::~SoundComponent()
{
    for(auto it = audio_sources.begin(); it != audio_sources.end(); it++)
    {
        if(it->second)
        {
            delete it->second;
        }
    }
}

void ge::SoundComponent::add(const std::string &name, AudioBuffer &audio, bool space)
{
    AudioSource *source = new AudioSource(audio, space);
    owner->get_component<ge::ShapePropertiesComponent>()
        .position().bilink(source->position_p());
    audio_sources[name] = source;
}

void ge::SoundComponent::del(const std::string &name)
{
    if(audio_sources.find(name) != audio_sources.end())
    {
        AudioSource *source = audio_sources[name];
        owner->get_component<ge::ShapePropertiesComponent>()
            .position().rm_link(source->position_p(), false);
        delete source;
        audio_sources.erase(name);
    }
}

ge::AudioSource *ge::SoundComponent::get(const std::string &name)
{
    if(audio_sources.find(name) != audio_sources.end())
        return audio_sources[name];
    return nullptr;
}

void ge::SoundComponent::play(const std::string &name, bool if_terminated)
{
    ge::AudioSource *source = get(name);
    if(source)
    {
        if(!if_terminated || !source->is_playing())
            source->play();
    }
}

