#include "ge/timer/timer.hpp"
#include <ge/core/timing.hpp>

ge::Timer::Timer(float max_duration_tm)
{
    max_duration_property.link<float>(&elapsed_time_property, [](const float& duration) {
        return 0;
    });
    max_duration_property.set(max_duration_tm);
    timeout_property.set(false);
    elapsed_time_property.link<bool>(&timeout_property, [this](float delta) {
        return delta >= max_duration().get();
    });
    timeout_property.on_change([&](bool timeout_value) {
        if(timeout_value)
        {
            if(ending_callback)
            {
                ending_callback(elapsed_time().get());
            }
        }
        else
        {
            if(during_callback)
            {
                during_callback(elapsed_time().get());
            }
        }
    });
}

bool ge::Timer::is_timeout()
{
    return timeout_property.get();
}

void ge::Timer::start()
{
    t0 = Timing::get_sec();
    t1 = t0;
    elapsed_time_property.set(t1 - t0);
}

void ge::Timer::run()
{
    if(!timeout_property.get())
    {
        t1 = Timing::get_sec();
        elapsed_time_property.set(t1 - t0);
    }
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
