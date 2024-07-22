#ifndef __GE_CALLBACK_COMPONENT_HPP__
#define __GE_CALLBACK_COMPONENT_HPP__
#include <ge/entity/components/component.hpp>
#include <functional>
#include <map>
#include <vector>

namespace ge
{
    class CallbackComponent : public UpdatableComponent
    {
    private:
        std::function<void(float dt)> callback;
    public:
        using UpdatableComponent::UpdatableComponent;
        virtual void update(float dt) override;
        void set(std::function<void(float dt)> callback);
    };

    class CallbacksComponent : public UpdatableComponent
    {
    private:
        std::vector<std::function<void(float dt)>> callbacks;
    public:
        using UpdatableComponent::UpdatableComponent;
        virtual void update(float dt) override;
        CallbacksComponent& add(std::function<void(float dt)> callback);
    };

    class NamedCallbacksComponent : public Component
    {
    private:
        std::map<std::string, std::function<void()>> named_callbacks;
    public:
        using Component::Component;
        NamedCallbacksComponent& set(const std::string& name, std::function<void()> callback);
        NamedCallbacksComponent& call(const std::string& name);
    };
}


#endif

