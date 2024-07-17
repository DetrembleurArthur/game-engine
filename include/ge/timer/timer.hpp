#ifndef __GE_TIMER_HPP__
#define __GE_TIMER_HPP__
#include <ge/binding/notify_property.hpp>

namespace ge
{
    class Timer
    {
    private:
        float t0=0.0;
        float t1=0.0;
        FloatNotifyProperty max_duration_property;
        FloatNotifyProperty elapsed_time_property;
        BoolNotifyProperty timeout_property;
        std::function<void(float)> during_callback;
        std::function<void(float)> ending_callback;
    public:
        Timer(float max_duration);
        bool is_timeout();
        void start();
        void run();
        FloatNotifyProperty& max_duration();
        FloatNotifyProperty& elapsed_time();
        BoolNotifyProperty& timeout();
        Timer &on_during(std::function<void(float)> callback);
        Timer &on_ending(std::function<void(float)> callback);
    };
}

#endif
