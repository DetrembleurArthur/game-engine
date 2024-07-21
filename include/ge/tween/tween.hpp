#ifndef __GE_TWEEN_HPP__
#define __GE_TWEEN_HPP__
#include <ge/binding/property.hpp>
#include <ge/tween/tween_functions.hpp>

namespace ge
{
    class TweenAbstract
    {
    public:
        virtual void set_progression(float perc) = 0;
    };

    template <typename T> class Tween : public TweenAbstract
    {
    protected:
        T from_value;
        T to_value;
        std::function<float(float)> tween_function=tweenf::linear;
        Property<T> *target=nullptr;
    public:
        Tween(Property<T> *target);
        Tween(Property<T> *target, T from, T to, std::function<float(float)> tween_function=tweenf::linear);
        Tween<T>& from(T value);
        Tween<T>& to(T value);
        Tween<T>& func(std::function<float(float)> tween_function);
        void swap();
        virtual void set_progression(float perc) override;
    };
}

#endif
