#include "ge/entity/components/timer_component.hpp"

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
    for(Timer *timer : timers)
    {
        if(timer)
        {
            timer->run();
        }
    }
}

ge::Timer &ge::TimerComponent::create(float duration_sec)
{
    ge::Timer *timer = new ge::Timer(duration_sec);
    timers.push_back(timer);
    timer->start();
    return *timer;
}

