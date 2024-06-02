#include "window_events.hpp"

std::function<void(const glm::vec2&)> ge::WindowEvents::on_window_size_changed_callback;
std::function<void(const glm::vec2&)> ge::WindowEvents::on_window_frame_buffer_size_changed_callback;
std::function<void(const glm::vec2&)> ge::WindowEvents::on_window_content_scale_changed_callback;
std::function<void(const glm::vec2&)> ge::WindowEvents::on_window_position_changed_callback;
std::function<void()> ge::WindowEvents::on_window_restored_callback;
std::function<void()> ge::WindowEvents::on_window_iconified_callback;
std::function<void()> ge::WindowEvents::on_window_maximized_callback;
std::function<void()> ge::WindowEvents::on_window_minimized_callback;
std::function<void()> ge::WindowEvents::on_window_focused_callback;
std::function<void()> ge::WindowEvents::on_window_unfocused_callback;
std::function<void()> ge::WindowEvents::on_window_refreshed_callback;

void ge::WindowEvents::set_on_window_size_changed(GLFWwindow *win, int width, int height)
{
    log("size changed: " + std::to_string(width) + "x" + std::to_string(height), LogLevels::WIN_EVENT);
    if(WindowEvents::on_window_size_changed_callback)
    {
        glm::vec2 size(width, height);
        WindowEvents::on_window_size_changed_callback(size);
    }
}

void ge::WindowEvents::set_on_window_frame_buffer_size_changed(GLFWwindow *win, int width, int height)
{
    log("frame buffer size changed: " + std::to_string(width) + "x" + std::to_string(height), LogLevels::WIN_EVENT);
    if(WindowEvents::on_window_size_changed_callback)
    {
        glm::vec2 size(width, height);
        glViewport(0, 0, width, height);
        WindowEvents::on_window_frame_buffer_size_changed_callback(size);
    }
}

void ge::WindowEvents::set_on_window_content_scale_changed(GLFWwindow *win, float xscale, float yscale)
{
    log("content scale changed: " + std::to_string(xscale) + "x" + std::to_string(yscale), LogLevels::WIN_EVENT);
    if(WindowEvents::on_window_size_changed_callback)
    {
        glm::vec2 scales(xscale, yscale);
        WindowEvents::on_window_content_scale_changed_callback(scales);
    }
}

void ge::WindowEvents::set_on_window_position_changed(GLFWwindow *win, int x, int y)
{
    log("position changed: (" + std::to_string(x) + ", " + std::to_string(y) + ")", LogLevels::WIN_EVENT);
    if(WindowEvents::on_window_position_changed_callback)
    {
        glm::vec2 pos(x, y);
        WindowEvents::on_window_position_changed_callback(pos);
    }
}

void ge::WindowEvents::set_on_window_iconify_restore_state_changed(GLFWwindow *win, int iconify)
{
    if(iconify)
    {
        log("iconified", LogLevels::WIN_EVENT);
        if(WindowEvents::on_window_iconified_callback)
        {
            WindowEvents::on_window_iconified_callback();
        }
    }
    else
    {
        log("restored", LogLevels::WIN_EVENT);
        if(WindowEvents::on_window_restored_callback)
        {
            WindowEvents::on_window_restored_callback();
        }
    }
}

void ge::WindowEvents::set_on_window_maximize_changed(GLFWwindow *win, int maximized)
{
    if(maximized)
    {
        log("maximized", LogLevels::WIN_EVENT);
        if(WindowEvents::on_window_maximized_callback)
        {
            WindowEvents::on_window_maximized_callback();
        }
    }
    else
    {
        log("minimized", LogLevels::WIN_EVENT);
        if(WindowEvents::on_window_minimized_callback)
        {
            WindowEvents::on_window_minimized_callback();
        }
    }
}

void ge::WindowEvents::set_on_window_focus_changed(GLFWwindow *win, int focused)
{
    if(focused)
    {
        log("focused", LogLevels::WIN_EVENT);
        if(WindowEvents::on_window_focused_callback)
        {
            WindowEvents::on_window_focused_callback();
        }
    }
    else
    {
        log("unfocused", LogLevels::WIN_EVENT);
        if(WindowEvents::on_window_unfocused_callback)
        {
            WindowEvents::on_window_unfocused_callback();
        }
    }
}

void ge::WindowEvents::set_on_window_refreshed_changed(GLFWwindow *win)
{
    log("refresh required", LogLevels::WIN_EVENT);
    if(WindowEvents::on_window_refreshed_callback)
    {
        WindowEvents::on_window_refreshed_callback();
    }
}

void ge::WindowEvents::init(GLFWwindow *window)
{
    log("initializing window events");
    glfwSetWindowSizeCallback(window, WindowEvents::set_on_window_size_changed);
    glfwSetFramebufferSizeCallback(window, WindowEvents::set_on_window_frame_buffer_size_changed);
    glfwSetWindowContentScaleCallback(window, WindowEvents::set_on_window_content_scale_changed);
    glfwSetWindowPosCallback(window, WindowEvents::set_on_window_position_changed);
    glfwSetWindowIconifyCallback(window, WindowEvents::set_on_window_iconify_restore_state_changed);
    glfwSetWindowMaximizeCallback(window, WindowEvents::set_on_window_maximize_changed);
    glfwSetWindowFocusCallback(window, WindowEvents::set_on_window_focus_changed);
    glfwSetWindowRefreshCallback(window, WindowEvents::set_on_window_refreshed_changed);
}

void ge::WindowEvents::on_window_size_changed(std::function<void(const glm::vec2&)> c)
{
    WindowEvents::on_window_size_changed_callback = c;
}

void ge::WindowEvents::on_window_frame_buffer_size_changed(std::function<void(const glm::vec2 &)> c)
{
    WindowEvents::on_window_frame_buffer_size_changed_callback = c;
}

void ge::WindowEvents::on_window_content_scale_changed(std::function<void(const glm::vec2 &)> c)
{
    WindowEvents::on_window_content_scale_changed_callback = c;
}

void ge::WindowEvents::on_window_position_changed(std::function<void(const glm::vec2 &)> c)
{
    WindowEvents::on_window_position_changed_callback = c;
}

void ge::WindowEvents::on_window_iconified(std::function<void()> c)
{
    WindowEvents::on_window_iconified_callback = c;
}

void ge::WindowEvents::on_window_restored(std::function<void()> c)
{
    WindowEvents::on_window_restored_callback = c;
}

void ge::WindowEvents::on_window_maximized(std::function<void()> c)
{
    WindowEvents::on_window_maximized_callback = c;
}

void ge::WindowEvents::on_window_minimized(std::function<void()> c)
{
    WindowEvents::on_window_minimized_callback = c;
}

void ge::WindowEvents::on_window_focused(std::function<void()> c)
{
    WindowEvents::on_window_focused_callback = c;
}

void ge::WindowEvents::on_window_unfocused(std::function<void()> c)
{
    WindowEvents::on_window_unfocused_callback = c;
}

void ge::WindowEvents::on_window_refreshed(std::function<void()> c)
{
    WindowEvents::on_window_refreshed_callback = c;
}
