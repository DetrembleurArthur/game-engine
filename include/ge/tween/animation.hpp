#ifndef __GE_ANIMATION_HPP__
#define __GE_ANIMATION_HPP__
#include <ge/tween/tween.hpp>
#include <ge/timer/timer.hpp>

namespace ge
{
    class AnimationAbstract
    {
    public:
        virtual void start() = 0;
        virtual void update() = 0;
        virtual Timer& get_timer() = 0;
    };

    template <typename T> class Animation : public AnimationAbstract
    {
    private:
        Tween<T> tween;
        Timer timer;
        bool backward=false;
        bool backward_index=true;
        std::function<void()> on_ending_callback;
    public:
        Animation(float duration, Property<T> *target, int period=0, bool backward=false);
        virtual void start() override;
        virtual void update() override;
        Tween<T>& get_tween();
        virtual Timer& get_timer() override;
        Animation& on_ending(std::function<void()> on_ending_callback);
    };
}

#endif
