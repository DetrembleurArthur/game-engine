#include "ge/entity/game_object.hpp"



ge::GameObject::GameObject() : flags({false, false})
{

}

ge::GameObject::~GameObject()
{
    for(Component *c : components)
    {
        if(c)
            delete c;
    }
    components.clear();
    std::cerr << "go deleted" << std::endl;
}


ge::Transform &ge::GameObject::get_transform()
{
    return transform;
}

void ge::GameObject::update(float dt)
{
    if(!flags.disabled)
    {
        for(Component *c : components)
        {
            if(dynamic_cast<UpdatableComponent *>(c))
            {
                dynamic_cast<UpdatableComponent *>(c)->update(dt);
            }
        }
    }
}

ge::GOFlags &ge::GameObject::get_flags()
{
    return flags;
}

ge::GameObject::operator Transform &()
{
    return transform;
}

ge::CallbackComponent &ge::GameObject::c_callback()
{
    return get_component<ge::CallbackComponent>();
}

ge::ColliderComponent &ge::GameObject::c_collider()
{
    return get_component<ge::ColliderComponent>();
}

ge::EventsComponent &ge::GameObject::c_event()
{
    return get_component<ge::EventsComponent>();
}

ge::SpriteComponent &ge::GameObject::c_sprite()
{
    return get_component<ge::SpriteComponent>();
}

ge::ShapePropertiesComponent &ge::GameObject::c_props()
{
    return get_component<ge::ShapePropertiesComponent>();
}

ge::ColorPropertiesComponent &ge::GameObject::c_color_props()
{
    return get_component<ge::ColorPropertiesComponent>();
}

ge::MoveComponent &ge::GameObject::c_move()
{
    return get_component<ge::MoveComponent>();
}
