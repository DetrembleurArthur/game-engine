#include "timing.hpp"
#include <GLFW/glfw3.h>

double ge::Timing::delta = 0.0;

double ge::Timing::get_sec()
{
    return glfwGetTime();
}

void ge::Timing::set(double time)
{
    glfwSetTime(time);
}

unsigned long ge::Timing::get_timer_value()
{
    return glfwGetTimerValue();
}

unsigned long ge::Timing::get_timer_freq()
{
    return glfwGetTimerFrequency();
}

void ge::Timing::set_delta(double delta)
{
    ge::Timing::delta = delta;
}

double ge::Timing::get_delta()
{
    return ge::Timing::delta;
}
