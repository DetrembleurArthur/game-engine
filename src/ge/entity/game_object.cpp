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
                //std::cout << "update " << typeid(*c).name() << std::endl;
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
