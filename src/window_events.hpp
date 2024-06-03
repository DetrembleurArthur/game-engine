#ifndef __GE_WINDOW_EVENTS_HPP__
#define __GE_WINDOW_EVENTS_HPP__
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <functional>
#include <log.hpp>
#include <vector>

namespace ge
{
    class WindowEvents
    {
    private:
        static std::function<void(const glm::vec2&)>         on_window_size_changed_callback;
        static std::function<void(const glm::vec2&)>         on_window_frame_buffer_size_changed_callback;
        static std::function<void(const glm::vec2&)>         on_window_content_scale_changed_callback;
        static std::function<void(const glm::vec2&)>         on_window_position_changed_callback;
        static std::function<void()>                         on_window_iconified_callback;
        static std::function<void()>                         on_window_restored_callback;
        static std::function<void()>                         on_window_maximized_callback;
        static std::function<void()>                         on_window_minimized_callback;
        static std::function<void()>                         on_window_focused_callback;
        static std::function<void()>                         on_window_unfocused_callback;
        static std::function<void()>                         on_window_refreshed_callback;
        static std::function<void(std::vector<std::string>)> on_window_drop_callback;
        static void set_on_window_size_changed(GLFWwindow *win, int width, int height);
        static void set_on_window_frame_buffer_size_changed(GLFWwindow *win, int width, int height);
        static void set_on_window_content_scale_changed(GLFWwindow *win, float scale, float yscale);
        static void set_on_window_position_changed(GLFWwindow *win, int x, int y);
        static void set_on_window_iconify_restore_state_changed(GLFWwindow *win, int iconify);
        static void set_on_window_maximize_changed(GLFWwindow *win, int maximized);
        static void set_on_window_focus_changed(GLFWwindow *win, int focused);
        static void set_on_window_refreshed_changed(GLFWwindow *win);
        static void set_on_window_drop(GLFWwindow *win, int count, const char **paths);
    public:
        static void init(GLFWwindow *window);
        static void on_window_size_changed(std::function<void(const glm::vec2&)> c);
        static void on_window_frame_buffer_size_changed(std::function<void(const glm::vec2&)> c);
        static void on_window_content_scale_changed(std::function<void(const glm::vec2&)> c);
        static void on_window_position_changed(std::function<void(const glm::vec2&)> c);
        static void on_window_iconified(std::function<void()> c);
        static void on_window_restored(std::function<void()> c);
        static void on_window_maximized(std::function<void()> c);
        static void on_window_minimized(std::function<void()> c);
        static void on_window_focused(std::function<void()> c);
        static void on_window_unfocused(std::function<void()> c);
        static void on_window_refreshed(std::function<void()> c);
        static void on_window_drop(std::function<void(std::vector<std::string>)> c);
    };
}


#endif
