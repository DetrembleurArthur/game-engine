#ifndef __GE_CALLBACK_COMPONENT_HPP__
#define __GE_CALLBACK_COMPONENT_HPP__
#include <component.hpp>
#include <functional>

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
}


#endif

