#include "ge/entity/components/animation_component.hpp"
#include "ge/entity/components/shape_properties_component.hpp"
#include <ge/entity/game_object.hpp>

ge::AnimationComponent::~AnimationComponent()
{
    for(Animation *animation : animations)
    {
        if(animation)
            delete animation;
    }
}

void ge::AnimationComponent::update(float dt)
{
    if(animation_required)
    {
        animations.insert(animations.end(), waiting_animations.begin(), waiting_animations.end());
        animation_required = false;
        waiting_animations.clear();
    }
    for(Animation *animation : animations)
    {
        if(animation)
        {
            animation->update();
            if(!clean_required && animation->get_timer().is_timeout())
            {
                clean_required = true;
            }
        }
    }
    if(clean_required)
    {
        auto it = std::remove_if(animations.begin(), animations.end(), [](Animation *animation) {
            bool timeout = animation->get_timer().is_timeout();
            if(timeout)
                delete animation;
            return timeout;
        });
        animations.erase(it, animations.end());
        clean_required = false;
    }
}

ge::Animation &ge::AnimationComponent::create(float duration, FloatProperty *target, int period, bool backward)
{
    ge::Animation *animation = new Animation(duration, target, period, backward);
    waiting_animations.push_back(animation);
    animation_required = true;
    return *animation;
}

ge::Animation &ge::AnimationComponent::to_x(float duration, float to, float from, int period, bool backward)
{
    ge::Animation& animation = create(duration, owner->get_component<ge::ShapePropertiesComponent>().p_x(), period, backward);
    animation.get_tween().from(from == std::numeric_limits<float>::max() ? owner->get_transform().get_x() : from).to(to);
    return animation;
}
