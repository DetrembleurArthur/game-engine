#include "ge/entity/components/animation_component.hpp"
#include "ge/entity/components/shape_properties_component.hpp"
#include "ge/entity/components/color_properties_component.hpp"
#include <ge/entity/game_object.hpp>

ge::AnimationComponent::~AnimationComponent()
{
    for(AnimationAbstract *animation : animations)
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
    for(AnimationAbstract *animation : animations)
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
        auto it = std::remove_if(animations.begin(), animations.end(), [](AnimationAbstract *animation) {
            bool timeout = animation->get_timer().is_timeout();
            if(timeout)
                delete animation;
            return timeout;
        });
        animations.erase(it, animations.end());
        clean_required = false;
    }
}

ge::Animation<float> &ge::AnimationComponent::to_x(float duration, float to, float from, int period, bool backward, std::function<float(float)> ftween)
{
    ge::Animation<float> *animation = new Animation<float>(duration, owner->get_component<ge::ShapePropertiesComponent>().p_x(), period, backward);
    animation->get_tween().from(from).to(to).func(ftween);
    animations.push_back(animation);
    animation_required = true;
    return *animation;
}

ge::Animation<float> &ge::AnimationComponent::to_y(float duration, float to, float from, int period, bool backward, std::function<float(float)> ftween)
{
    ge::Animation<float> *animation = new Animation<float>(duration, owner->get_component<ge::ShapePropertiesComponent>().p_y(), period, backward);
    animation->get_tween().from(from).to(to).func(ftween);
    animations.push_back(animation);
    animation_required = true;
    return *animation;
}

ge::Animation<glm::vec2> &ge::AnimationComponent::to_position(float duration, glm::vec2 to, glm::vec2 from, int period, bool backward, std::function<float(float)> ftween)
{
    ge::Animation<glm::vec2> *animation = new Animation<glm::vec2>(duration, owner->get_component<ge::ShapePropertiesComponent>().p_position(), period, backward);
    animation->get_tween().from(from).to(to).func(ftween);
    animations.push_back(animation);
    animation_required = true;
    return *animation;
}

ge::Animation<float> &ge::AnimationComponent::to_width(float duration, float to, float from, int period, bool backward, std::function<float(float)> ftween)
{
    ge::Animation<float> *animation = new Animation<float>(duration, owner->get_component<ge::ShapePropertiesComponent>().p_width(), period, backward);
    animation->get_tween().from(from).to(to).func(ftween);
    animations.push_back(animation);
    animation_required = true;
    return *animation;
}

ge::Animation<float> &ge::AnimationComponent::to_height(float duration, float to, float from, int period, bool backward, std::function<float(float)> ftween)
{
    ge::Animation<float> *animation = new Animation<float>(duration, owner->get_component<ge::ShapePropertiesComponent>().p_height(), period, backward);
    animation->get_tween().from(from).to(to).func(ftween);
    animations.push_back(animation);
    animation_required = true;
    return *animation;
}

ge::Animation<glm::vec2> &ge::AnimationComponent::to_size(float duration, glm::vec2 to, glm::vec2 from, int period, bool backward, std::function<float(float)> ftween)
{
    ge::Animation<glm::vec2> *animation = new Animation<glm::vec2>(duration, owner->get_component<ge::ShapePropertiesComponent>().p_size(), period, backward);
    animation->get_tween().from(from).to(to).func(ftween);
    animations.push_back(animation);
    animation_required = true;
    return *animation;
}

ge::Animation<float> &ge::AnimationComponent::to_rotation(float duration, float to, float from, int period, bool backward, std::function<float(float)> ftween)
{
    ge::Animation<float> *animation = new Animation<float>(duration, owner->get_component<ge::ShapePropertiesComponent>().p_rotation(), period, backward);
    animation->get_tween().from(from).to(to).func(ftween);
    animations.push_back(animation);
    animation_required = true;
    return *animation;
}

ge::Animation<float> &ge::AnimationComponent::to_r(float duration, float to, float from, int period, bool backward, std::function<float(float)> ftween)
{
    ge::Animation<float> *animation = new Animation<float>(duration, owner->get_component<ge::ColorPropertiesComponent>().p_red(), period, backward);
    animation->get_tween().from(from).to(to).func(ftween);
    animations.push_back(animation);
    animation_required = true;
    return *animation;
}

ge::Animation<float> &ge::AnimationComponent::to_g(float duration, float to, float from, int period, bool backward, std::function<float(float)> ftween)
{
    ge::Animation<float> *animation = new Animation<float>(duration, owner->get_component<ge::ColorPropertiesComponent>().p_green(), period, backward);
    animation->get_tween().from(from).to(to).func(ftween);
    animations.push_back(animation);
    animation_required = true;
    return *animation;
}

ge::Animation<float> &ge::AnimationComponent::to_b(float duration, float to, float from, int period, bool backward, std::function<float(float)> ftween)
{
    ge::Animation<float> *animation = new Animation<float>(duration, owner->get_component<ge::ColorPropertiesComponent>().p_blue(), period, backward);
    animation->get_tween().from(from).to(to).func(ftween);
    animations.push_back(animation);
    animation_required = true;
    return *animation;
}

ge::Animation<float> &ge::AnimationComponent::to_a(float duration, float to, float from, int period, bool backward, std::function<float(float)> ftween)
{
    ge::Animation<float> *animation = new Animation<float>(duration, owner->get_component<ge::ColorPropertiesComponent>().p_alpha(), period, backward);
    animation->get_tween().from(from).to(to).func(ftween);
    animations.push_back(animation);
    animation_required = true;
    return *animation;
}

ge::Animation<glm::vec4> &ge::AnimationComponent::to_color(float duration, glm::vec4 to, glm::vec4 from, int period, bool backward, std::function<float(float)> ftween)
{
    ge::Animation<glm::vec4> *animation = new Animation<glm::vec4>(duration, owner->get_component<ge::ColorPropertiesComponent>().p_color(), period, backward);
    animation->get_tween().from(from).to(to).func(ftween);
    animations.push_back(animation);
    animation_required = true;
    return *animation;
}

