#ifndef __GE_TWEEN_HPP__
#define __GE_TWEEN_HPP__
#include <ge/binding/property.hpp>
#include <ge/tween/tween_functions.hpp>

namespace ge
{
    class Tween
    {
    private:
        float from_value;
        float to_value;
        std::function<float(float)> tween_function=tweenf::linear;
        FloatProperty *target=nullptr;
    public:
        Tween(FloatProperty *target);
        Tween(FloatProperty *target, float from, float to, std::function<float(float)> tween_function=tweenf::linear);
        void set_progression(float perc);
        Tween& from(float value);
        Tween& to(float value);
        Tween& func(std::function<float(float)> tween_function);
        void swap();
    };
}

#endif
