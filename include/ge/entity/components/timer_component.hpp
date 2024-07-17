#ifndef __GE_TIMER_COMPONENT_HPP__
#define __GE_TIMER_COMPONENT_HPP__
#include <ge/entity/components/component.hpp>
#include <ge/timer/timer.hpp>
#include <vector>

namespace ge
{
    class TimerComponent : public UpdatableComponent
    {
    private:
        std::vector<Timer *> timers;
    public:
        using UpdatableComponent::UpdatableComponent;
        virtual ~TimerComponent();
        virtual void update(float dt) override;
        ge::Timer& create(float duration_sec);
    };
}

#endif
