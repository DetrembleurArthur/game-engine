#ifndef __GE_CONTROLLER_EVENTS_HPP__
#define __GE_CONTROLLER_EVENTS_HPP__
#include <functional>
#include <GLFW/glfw3.h>
#include <log.hpp>
#include <glm/glm.hpp>
#include <controller_input.hpp>

namespace ge
{
    class ControllerEvents
    {
    private:
        static std::function<void(int jid)> on_joystick_connected_callback;
        static std::function<void(int jid)> on_joystick_disconnected_callback;
        static void set_on_joystick(int jid, int event);
    public:
        static void init();
        static void on_joystick_connected(std::function<void(int)> c);
        static void on_joystick_disconnected(std::function<void(int)> c);
    };
}

#endif
