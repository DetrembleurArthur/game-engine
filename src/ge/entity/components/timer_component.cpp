#include "ge/entity/components/timer_component.hpp"
#include <iostream>

ge::TimerComponent::~TimerComponent()
{
    for(Timer *timer : timers)
    {
        if(timer)
        {
            delete timer;
        }
    }
}

void ge::TimerComponent::update(float dt)
{
    if(timer_required)
    {
        timers.insert(timers.end(), waiting_timers.begin(), waiting_timers.end());
        timer_required = false;
        waiting_timers.clear();
    }
    for(Timer *timer : timers)
    {
        if(timer)
        {
            timer->run();
            if(!cleanup_required && timer->is_timeout())
                cleanup_required = true;
        }
    }
    if(cleanup_required)
    {
        auto it = std::remove_if(timers.begin(), timers.end(), [](Timer *timer) {
            bool timeout = timer->is_timeout();
            if(timeout)
                delete timer;
            return timeout;
        });
        timers.erase(it, timers.end());
        cleanup_required = false;
    }
}

ge::Timer &ge::TimerComponent::create(float duration_sec, int period)
{
    ge::Timer *timer = new ge::Timer(duration_sec, period);
    waiting_timers.push_back(timer);
    timer_required = true;
    return *timer;
}

