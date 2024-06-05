#include "controller_input.hpp"
#include <iostream>

std::unordered_map<int, ge::Controller> ge::ControllerInput::controllers;

bool ge::ControllerInput::is_present(int joystick_id)
{
    return glfwJoystickPresent(joystick_id);
}

ge::Controller &ge::ControllerInput::get(int jid)
{
    if(jid == -1)
    {
        for(int i = 0; i <= GLFW_JOYSTICK_LAST; i++)
        {
            if(ControllerInput::controllers.find(i) != ControllerInput::controllers.end())
            {
                if(ControllerInput::is_present(i))
                {
                    return ControllerInput::controllers[i];
                }
            }
        }
    }
    if(ControllerInput::controllers.find(jid) == ControllerInput::controllers.end())
    {
        if(ControllerInput::is_present(jid))
        {
            activate(jid);
        }
    }
    return ControllerInput::controllers[jid];
}

void ge::ControllerInput::activate(int jid)
{
    ControllerInput::controllers[jid] = Controller(jid);
}

void ge::ControllerInput::disactivate(int jid)
{
    ControllerInput::controllers.erase(jid);
}

void ge::ControllerInput::update_controllers()
{
    for (auto it = ControllerInput::controllers.begin(); it != ControllerInput::controllers.end(); ++it)
    {
        if(it->second.is_gamepad())
            it->second.update_gamepad();
    }
}

ge::Controller::Controller(int id) : id(id)
{
}

std::vector<unsigned char> &ge::Controller::get_buttons(bool extract)
{
    if(extract || buttons.empty())
    {
        buttons.clear();
        int count = 0;
        const unsigned char *cbuttons = glfwGetJoystickButtons(id, &count);
        for(int i = 0; i < count; i++)
        {
            buttons.push_back(cbuttons[i]);
        }
    }
    return buttons;
}

std::vector<unsigned char> &ge::Controller::get_hats(bool extract)
{
    if(extract || hats.empty())
    {
        hats.clear();
        int count = 0;
        const unsigned char *chats = glfwGetJoystickHats(id, &count);
        for(int i = 0; i < count; i++)
        {
            hats.push_back(chats[i]);
        }
    }
    return hats;
}

std::string ge::Controller::get_name()
{
    return std::string(glfwGetJoystickName(id));
}

bool ge::Controller::is_gamepad()
{
    return glfwJoystickIsGamepad(id);
}

std::string ge::Controller::get_gamepad_name()
{
    return std::string(glfwGetGamepadName(id));
}

void ge::Controller::update_gamepad()
{
    glfwGetGamepadState(id, (GLFWgamepadstate *)&gamepad_buttons);
}

std::vector<float> &ge::Controller::get_axes(bool extract)
{
    if(extract || axes.empty())
    {
        axes.clear();
        int count = 0;
        const float *caxes = glfwGetJoystickAxes(id, &count);
        for(int i = 0; i < count; i++)
        {
            axes.push_back(caxes[i]);
        }
    }
    return axes;
}
