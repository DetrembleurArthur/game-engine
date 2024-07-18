#include "ge/timer/timer.hpp"
#include <ge/core/timing.hpp>
#include <iostream>


const int ge::Timer::INF = -1;

ge::Timer::Timer(float max_duration_tm, int period) : period(period)
{
    max_duration_property.link<float>(&elapsed_time_property, [](const float& duration) {
        return 0;
    });
    max_duration_property.set(max_duration_tm);
    timeout_property.set(false);
    elapsed_time_property.link<bool>(&timeout_property, [this](float delta) {
        return delta >= max_duration_property.get();
    });
    timeout_property.on_change([&](bool timeout_value) {
        if(timeout_value)
        {
            if(ending_callback)
            {
                ending_callback(elapsed_time_property.get());
            }
            if(period)
            {
                if((period > 0 && period_counter_property.get() < period) || period < 0)
                {
                    period_counter_property.set(period_counter_property.get() + 1);
                    start();
                }
            }
        }
        else
        {
            if(during_callback)
            {
                during_callback(elapsed_time_property.get());
            }
        }
    });
    period_counter_property.set(0);
}

bool ge::Timer::is_timeout()
{
    if(period < 0)
        return false;
    return timeout_property.get() && (period_counter_property.get() >= period);
}

void ge::Timer::start()
{
    t0 = Timing::get_sec();
    t1 = t0;
}

void ge::Timer::run()
{
    if(!is_timeout())
    {
        if(t0 == 0)
            start();
        t1 = Timing::get_sec();
        elapsed_time_property.set(t1 - t0);
    }
}

void ge::Timer::abort()
{
    t0 = 0.0;
    period=0;
    during_callback = [](float){};
    ending_callback = [](float){};
}

float ge::Timer::get_progression()
{
    return elapsed_time_property.get() / max_duration_property.get();
}

ge::FloatNotifyProperty &ge::Timer::max_duration()
{
    return max_duration_property;
}

ge::FloatNotifyProperty &ge::Timer::elapsed_time()
{
    return elapsed_time_property;
}

ge::BoolNotifyProperty &ge::Timer::timeout()
{
    return timeout_property;
}

ge::Timer &ge::Timer::on_during(std::function<void(float)> callback)
{
    this->during_callback = callback;
    return *this;
}

ge::Timer &ge::Timer::on_ending(std::function<void(float)> callback)
{
    this->ending_callback = callback;
    return *this;
}

ge::IntNotifyProperty &ge::Timer::period_counter()
{
    return period_counter_property;
}
