#include "ge/tween/animation.hpp"
#include <iostream>
ge::Animation::Animation(float duration, FloatProperty *target, int period, bool backward) : timer(duration, backward ? period * 2 : period), tween(target), backward(backward)
{
    timer.on_during([this](float elapsed) {
        if(backward_index == 1)
            tween.set_progression(timer.get_progression());
        else
            tween.set_progression(1 - timer.get_progression());
    });
    timer.on_ending([this](float elapsed) {
        if(this->backward)
        {
            backward_index = !backward_index;
        }
    });
}

void ge::Animation::start()
{
    timer.period_counter().set(0);
    timer.start();
    backward_index = 1;
}

void ge::Animation::update()
{
    if(!timer.is_timeout())
    {
        timer.run();
        if(timer.is_timeout())
        {
            if(backward_index != 1 || !backward)
                tween.set_progression(1.0);
            else
                tween.set_progression(0.0);
            on_ending_callback();
            on_ending_callback = [](){};
        }
    }
}

ge::Tween& ge::Animation::get_tween()
{
    return tween;
}

ge::Timer& ge::Animation::get_timer()
{
    return timer;
}

ge::Animation &ge::Animation::on_ending(std::function<void()> on_ending_callback)
{
    this->on_ending_callback = on_ending_callback;
    return *this;
}
