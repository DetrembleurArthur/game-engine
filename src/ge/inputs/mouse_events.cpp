#include "ge/inputs/mouse_events.hpp"

std::function<void(glm::vec2)> ge::MouseEvents::on_mouse_position_callback;
std::function<void()> ge::MouseEvents::on_mouse_enter_callback;
std::function<void()> ge::MouseEvents::on_mouse_leave_callback;
std::function<void(int, int, int)> ge::MouseEvents::on_mouse_button_callback;
std::function<void(glm::vec2)> ge::MouseEvents::on_mouse_scroll_callback;

void ge::MouseEvents::set_on_mouse_position_changed(GLFWwindow *win, double x, double y)
{
    //log("position: (" + std::to_string(x) + ", " + std::to_string(y) + ")", LogLevels::MOUSE_EVENT);
    if(on_mouse_position_callback)
    {
        glm::vec2 position(x, y);
        on_mouse_position_callback(position);
    }
}

void ge::MouseEvents::set_on_mouse_enter(GLFWwindow *win, int enter)
{
    if(enter)
    {
        log("enter", LogLevels::MOUSE_EVENT);
        if(on_mouse_enter_callback)
        {
            on_mouse_enter_callback();
        }
    }
    else
    {
        log("leave", LogLevels::MOUSE_EVENT);
        if(on_mouse_leave_callback)
        {
            on_mouse_leave_callback();
        }
    }
}

void ge::MouseEvents::set_on_mouse_button(GLFWwindow *win, int btn, int action, int mods)
{
    log("button-" + std::string(action == GLFW_PRESS ? "pressed" : (action == GLFW_RELEASE ? "released" : "repeated")) + ": btn=" + std::to_string(btn));
    if(on_mouse_button_callback)
    {
        on_mouse_button_callback(btn, action, mods);
    }
}

void ge::MouseEvents::set_on_mouse_scroll(GLFWwindow *win, double xoffset, double yoffset)
{
    log("scroll: (" + std::to_string(xoffset) + ", " + std::to_string(yoffset) + ")", LogLevels::MOUSE_EVENT);
    if(on_mouse_scroll_callback)
    {
        glm::vec2 offset(xoffset, yoffset);
        on_mouse_scroll_callback(offset);
    }
}

void ge::MouseEvents::init(GLFWwindow *window)
{
    glfwSetCursorPosCallback(window, MouseEvents::set_on_mouse_position_changed);
    glfwSetCursorEnterCallback(window, MouseEvents::set_on_mouse_enter);
    glfwSetMouseButtonCallback(window, MouseEvents::set_on_mouse_button);
    glfwSetScrollCallback(window, MouseEvents::set_on_mouse_scroll);
}

void ge::MouseEvents::on_mouse_position_changed(std::function<void(glm::vec2)> c)
{
    MouseEvents::on_mouse_position_callback = c;
}

void ge::MouseEvents::on_mouse_enter(std::function<void()> c)
{
    MouseEvents::on_mouse_enter_callback = c;
}

void ge::MouseEvents::on_mouse_leave(std::function<void()> c)
{
    MouseEvents::on_mouse_leave_callback = c;
}

void ge::MouseEvents::on_mouse_button(std::function<void(int, int, int)> c)
{
    MouseEvents::on_mouse_button_callback = c;
}

void ge::MouseEvents::on_mouse_scroll(std::function<void(glm::vec2)> c)
{
    MouseEvents::on_mouse_scroll_callback = c;
}
