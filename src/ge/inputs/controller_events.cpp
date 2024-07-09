#include "ge/inputs/controller_events.hpp"
#include <GLFW/glfw3.h>
#include <ge/utils/log.hpp>
#include <glm/glm.hpp>
#include <ge/inputs/controller_input.hpp>

std::function<void(int jid)> ge::ControllerEvents::on_joystick_connected_callback;
std::function<void(int jid)> ge::ControllerEvents::on_joystick_disconnected_callback;

void ge::ControllerEvents::set_on_joystick(int jid, int event)
{
    if(event == GLFW_CONNECTED)
    {
        log("joystick connected: " + std::to_string(jid), LogLevels::CONTROLLER_EVENT);
        ControllerInput::activate(jid);
        if(on_joystick_connected_callback)
        {
            on_joystick_connected_callback(jid);
        }
    }
    else
    {
        log("joystick disconnected: " + std::to_string(jid), LogLevels::CONTROLLER_EVENT);
        ControllerInput::disactivate(jid);
        if(on_joystick_disconnected_callback)
        {
            on_joystick_disconnected_callback(jid);
        }
    }
}

void ge::ControllerEvents::init()
{
    glfwSetJoystickCallback(ControllerEvents::set_on_joystick);
}

void ge::ControllerEvents::on_joystick_connected(std::function<void(int)> c)
{
    ControllerEvents::on_joystick_connected_callback = c;
}

void ge::ControllerEvents::on_joystick_disconnected(std::function<void(int)> c)
{
    ControllerEvents::on_joystick_disconnected_callback = c;
}

