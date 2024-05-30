#include "window_events.hpp"

std::function<void(const glm::vec2&)> ge::WindowEvents::on_window_size_changed_callback;
std::function<void(const glm::vec2&)> ge::WindowEvents::on_window_frame_buffer_size_changed_callback;
std::function<void(const glm::vec2&)> ge::WindowEvents::on_window_content_scale_changed_callback;
std::function<void(const glm::vec2&)> ge::WindowEvents::on_window_position_changed_callback;

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

void ge::WindowEvents::init(GLFWwindow *window)
{
    log("initializing window events");
    glfwSetWindowSizeCallback(window, WindowEvents::set_on_window_size_changed);
    glfwSetFramebufferSizeCallback(window, WindowEvents::set_on_window_frame_buffer_size_changed);
    glfwSetWindowContentScaleCallback(window, WindowEvents::set_on_window_content_scale_changed);
    glfwSetWindowPosCallback(window, WindowEvents::set_on_window_position_changed);
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
