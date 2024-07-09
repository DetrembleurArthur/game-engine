#ifndef __GE_MOUSE_EVENTS_HPP__
#define __GE_MOUSE_EVENTS_HPP__
#include <functional>
#include <GLFW/glfw3.h>
#include <ge/utils/log.hpp>
#include <glm/glm.hpp>

namespace ge
{
    class MouseEvents
    {
    private:
        static std::function<void(glm::vec2)> on_mouse_position_callback;
        static std::function<void()> on_mouse_enter_callback;
        static std::function<void()> on_mouse_leave_callback;
        static std::function<void(int, int, int)> on_mouse_button_callback;
        static std::function<void(glm::vec2)> on_mouse_scroll_callback;
        static void set_on_mouse_position_changed(GLFWwindow *win, double x, double y);
        static void set_on_mouse_enter(GLFWwindow *win, int enter);
        static void set_on_mouse_button(GLFWwindow *win, int btn, int action, int mods);
        static void set_on_mouse_scroll(GLFWwindow *win, double xoffset, double yoffset);
    public:
        static void init(GLFWwindow *window);
        static void on_mouse_position_changed(std::function<void(glm::vec2)> c);
        static void on_mouse_enter(std::function<void()> c);
        static void on_mouse_leave(std::function<void()> c);
        static void on_mouse_button(std::function<void(int, int, int)> c);
        static void on_mouse_scroll(std::function<void(glm::vec2)> c);
    };
}

#endif
