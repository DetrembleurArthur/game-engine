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
        bool cleanup_required=false;
        bool timer_required=false;
        std::vector<Timer *> timers;
        std::vector<Timer *> waiting_timers;
    public:
        using UpdatableComponent::UpdatableComponent;
        virtual ~TimerComponent();
        virtual void update(float dt) override;
        ge::Timer& create(float duration_sec, int period=0);
    };
}

#endif
