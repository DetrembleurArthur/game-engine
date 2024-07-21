#include "ge/tween/animation.hpp"

template <typename T> ge::Animation<T>::Animation(float duration, ge::Property<T> *target, int period, bool backward) : timer(duration, backward ? period * 2 : period), tween(target), backward(backward)
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

template <typename T> void ge::Animation<T>::start()
{
    timer.period_counter().set(0);
    timer.start();
    backward_index = 1;
}

template <typename T> void ge::Animation<T>::update()
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

template <typename T> ge::Tween<T>& ge::Animation<T>::get_tween()
{
    return tween;
}

template <typename T> ge::Timer& ge::Animation<T>::get_timer()
{
    return timer;
}

template <typename T> ge::Animation<T> &ge::Animation<T>::on_ending(std::function<void()> on_ending_callback)
{
    this->on_ending_callback = on_ending_callback;
    return *this;
}

template class ge::Animation<float>;
template class ge::Animation<glm::vec2>;
template class ge::Animation<glm::vec3>;
template class ge::Animation<glm::vec4>;
