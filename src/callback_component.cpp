#include "callback_component.hpp"

void ge::CallbackComponent::update(float dt)
{
    if(callback)
        callback(dt);
}

void ge::CallbackComponent::set(std::function<void(float dt)> callback)
{
    this->callback = callback;
}
