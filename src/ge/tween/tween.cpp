#include "ge/tween/tween.hpp"

template <typename T> ge::Tween<T>::Tween(Property<T> *target) : target(target)
{

}

template <typename T> ge::Tween<T>::Tween(Property<T> *target, T from, T to, std::function<float(float)> tween_function)
    : target(target), from_value(from), to_value(to), tween_function(tween_function)
{
}


template <typename T> ge::Tween<T>& ge::Tween<T>::from(T value)
{
    from_value = value;
    return *this;
}

template <typename T> ge::Tween<T>& ge::Tween<T>::to(T value)
{
    to_value = value;
    return *this;
}

template <typename T> ge::Tween<T>& ge::Tween<T>::func(std::function<float(float)> tween_function)
{
    this->tween_function = tween_function;
    return *this;
}

template <typename T> void ge::Tween<T>::swap()
{
    T tmp = from_value;
    from_value = to_value;
    to_value = tmp;
}

template <typename T> void ge::Tween<T>::set_progression(float perc)
{
    if(perc < 0)
        perc = 0;
    else if(perc > 1)
        perc = 1;
    if(target)
    {
        T interval = to_value - from_value;
        target->set(from_value + tween_function(perc) * interval);
    }
}

template class ge::Tween<float>;
template class ge::Tween<glm::vec2>;
template class ge::Tween<glm::vec3>;
template class ge::Tween<glm::vec4>;
