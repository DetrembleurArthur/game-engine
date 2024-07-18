#include "ge/tween/tween.hpp"

ge::Tween::Tween(FloatProperty *target) : target(target)
{

}

ge::Tween::Tween(FloatProperty *target, float from, float to, std::function<float(float)> tween_function)
    : target(target), from_value(from), to_value(to), tween_function(tween_function)
{
}

void ge::Tween::set_progression(float perc)
{
    if(perc < 0)
        perc = 0;
    else if(perc > 1)
        perc = 1;
    if(target)
    {
        float interval = to_value - from_value;
        target->set(from_value + tween_function(perc) * interval);
    }
}

ge::Tween& ge::Tween::from(float value)
{
    from_value = value;
    return *this;
}

ge::Tween& ge::Tween::to(float value)
{
    to_value = value;
    return *this;
}

ge::Tween& ge::Tween::func(std::function<float(float)> tween_function)
{
    this->tween_function = tween_function;
    return *this;
}

void ge::Tween::swap()
{
    float tmp = from_value;
    from_value = to_value;
    to_value = tmp;
}


