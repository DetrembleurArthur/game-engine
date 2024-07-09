#ifndef __GE_TIMING_HPP__
#define __GE_TIMING_HPP__

namespace ge
{
    class Timing
    {
    private:
        static double delta;
    public:
        static double get_sec();
        static void set(double time);
        static unsigned long get_timer_value();
        static unsigned long get_timer_freq();
        static void set_delta(double delta);
        static double get_delta();
    };
}

#endif
