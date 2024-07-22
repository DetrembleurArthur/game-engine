#include "ge/entity/components/callback_component.hpp"

void ge::CallbackComponent::update(float dt)
{
    if(callback)
        callback(dt);
}

void ge::CallbackComponent::set(std::function<void(float dt)> callback)
{
    this->callback = callback;
}

void ge::CallbacksComponent::update(float dt)
{
    for(std::function<void(float)>& callback : callbacks)
    {
        if(callback)
            callback(dt);
    }
}

ge::CallbacksComponent &ge::CallbacksComponent::add(std::function<void(float dt)> callback)
{
    callbacks.push_back(callback);
    return *this;
}

ge::NamedCallbacksComponent &ge::NamedCallbacksComponent::set(const std::string &name, std::function<void()> callback)
{
    named_callbacks[name] = callback;
    return *this;
}

ge::NamedCallbacksComponent &ge::NamedCallbacksComponent::call(const std::string &name)
{
    named_callbacks[name]();
    return *this;
}
