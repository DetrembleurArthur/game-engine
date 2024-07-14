#include "ge/entity/components/sprite_component.hpp"
#include <ge/core/timing.hpp>
#include <ge/entity/drawable.hpp>

ge::SpriteComponent::SpriteComponent(GameObject *go) : UpdatableComponent(go)
{
    if(!dynamic_cast<Drawable *>(go))
    {
        log("SpriteComponent must be used only for Drawable object", LogLevels::ERROR);
    }
}

void ge::SpriteComponent::set_spritesheet(ge::SpriteSheet *ss)
{
    spritesheet = ss;
    t0 = ge::Timing::get_sec();
    ge::Drawable *dr = dynamic_cast<Drawable *>(owner);
    if(dr)
        dr->set_texture(ss->get_texture());
}

void ge::SpriteComponent::set_frequency(float fr)
{
    frequency = fr;
}

void ge::SpriteComponent::update(float dt)
{
    if(spritesheet && sprite_set)
    {
        double elapsed = ge::Timing::get_sec() - t0;
        if(elapsed >= 1.0 / frequency)
        {
            sprite_index = (sprite_index + 1) % sprite_set->size();
            Drawable *dr = dynamic_cast<Drawable *>(owner);
            if(dr)
            {
                dr->update_uvs((*sprite_set)[sprite_index].uvs, spritesheet->get_uvs_size());
            }
            t0 = ge::Timing::get_sec();
        }
    }
}

void ge::SpriteComponent::set_sprite_set(const std::string &name)
{
    if(sprite_set == &spritesheet->get_sprite_set(name))
        return;
    sprite_set = &spritesheet->get_sprite_set(name);
    sprite_index = 0;
    t0 = ge::Timing::get_sec();
    Drawable *dr = dynamic_cast<Drawable *>(owner);
    if(dr)
        dr->update_uvs((*sprite_set)[sprite_index].uvs, spritesheet->get_uvs_size());
}
