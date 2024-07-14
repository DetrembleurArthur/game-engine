#ifndef __GE_SPRITE_COMPONENT_HPP__
#define __GE_SPRITE_COMPONENT_HPP__
#include <ge/entity/components/component.hpp>
#include <ge/graphics/sprite_sheet.hpp>

namespace ge
{
    class SpriteComponent : public ge::UpdatableComponent
    {
    private:
        ge::SpriteSheet *spritesheet=nullptr;
        const std::vector<ge::Sprite> *sprite_set=nullptr;
        int sprite_index=0;
        float frequency=1.0; // sprite per second
        float t0=0;
    public:
        SpriteComponent(GameObject *go);
        void set_spritesheet(ge::SpriteSheet *ss);
        void set_frequency(float fr);
        void update(float dt) override;
        void set_sprite_set(const std::string& name);
    };
}


#endif

