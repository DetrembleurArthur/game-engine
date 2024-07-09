#include "ge/entity/components/component.hpp"

ge::Component::Component(GameObject *owner) : owner(owner)
{
}

ge::Component::~Component()
{
}

ge::GameObject *ge::Component::get_owner()
{
    return owner;
}
