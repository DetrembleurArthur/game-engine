#ifndef __GE_ANIMATION_HPP__
#define __GE_ANIMATION_HPP__
#include <ge/tween/tween.hpp>
#include <ge/timer/timer.hpp>

namespace ge
{
    class Animation
    {
    private:
        Tween tween;
        Timer timer;
        bool backward=false;
        bool backward_index=true;
        std::function<void()> on_ending_callback;
    public:
        Animation(float duration, FloatProperty *target, int period=0, bool backward=false);
        void start();
        void update();
        Tween& get_tween();
        Timer& get_timer();
        Animation& on_ending(std::function<void()> on_ending_callback);
    };
}

#endif
