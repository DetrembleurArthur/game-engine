#ifndef __GE_WINDOW_EVENTS_HPP__
#define __GE_WINDOW_EVENTS_HPP__
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <functional>
#include <log.hpp>

namespace ge
{
    class WindowEvents
    {
    private:
        static std::function<void(const glm::vec2&)> on_window_size_changed_callback;
        static std::function<void(const glm::vec2&)> on_window_frame_buffer_size_changed_callback;
        static std::function<void(const glm::vec2&)> on_window_content_scale_changed_callback;
        static std::function<void(const glm::vec2&)> on_window_position_changed_callback;
        static void set_on_window_size_changed(GLFWwindow *win, int width, int height);
        static void set_on_window_frame_buffer_size_changed(GLFWwindow *win, int width, int height);
        static void set_on_window_content_scale_changed(GLFWwindow *win, float scale, float yscale);
        static void set_on_window_position_changed(GLFWwindow *win, int x, int y);
    public:
        static void init(GLFWwindow *window);
        static void on_window_size_changed(std::function<void(const glm::vec2&)> c);
        static void on_window_frame_buffer_size_changed(std::function<void(const glm::vec2&)> c);
        static void on_window_content_scale_changed(std::function<void(const glm::vec2&)> c);
        static void on_window_position_changed(std::function<void(const glm::vec2&)> c);
    };
}


#endif
