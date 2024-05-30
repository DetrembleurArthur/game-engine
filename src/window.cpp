#include "window.hpp"

ge::Window::Window(const std::string &title, unsigned width, unsigned height)
{
    log("window creation: " + title + " (" + std::to_string(width) + "x" + std::to_string(height) + ")");
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if(is_created())
    {
        log("window creation success");
        WindowEvents::init(window);
    }
    else
    {
        log("window creation failed", LogLevels::ERROR);
    }
}

ge::Window::~Window()
{
    if(is_created())
    {
        glfwDestroyWindow(window);
        log("window destroyed");
    }
}

void ge::Window::make_current()
{
    glfwMakeContextCurrent(window);
}

bool ge::Window::must_be_closed() const
{
    return glfwWindowShouldClose(window);
}

void ge::Window::clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void ge::Window::swap()
{
    glfwSwapBuffers(window);
}

void ge::Window::poll_events()
{
    glfwPollEvents();
}

bool ge::Window::is_created() const
{
    return window != nullptr;
}

void ge::Window::close()
{
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void ge::Window::set_monitor(Monitor &monitor)
{
    const GLFWvidmode mode = monitor.get_video_mode();
    glfwSetWindowMonitor(window, monitor.get_pointer(), 0, 0, mode.width, mode.height, mode.refreshRate);
}

void ge::Window::set_size(glm::uvec2 size)
{
    glfwSetWindowSize(window, size.x, size.y);
}

void ge::Window::set_limits(int min_width, int min_height, int max_width, int max_height)
{
    glfwSetWindowSizeLimits(window, min_width, min_height, max_width, max_height);
}

void ge::Window::set_aspect_ratio(int num, int den)
{
    if(num == 0 || den == 0)
    {
        glm::uvec2&& size = get_size();
        num = size.x;
        den = size.y;
    }
    glfwSetWindowAspectRatio(window, num, den);
}

void ge::Window::set_position(glm::vec2 position)
{
    glfwSetWindowPos(window, position.x, position.y);
}

void ge::Window::set_title(const std::string &title)
{
    glfwSetWindowTitle(window, title.c_str());
}

glm::uvec2 ge::Window::get_size()
{
    int w, h;
    glfwGetWindowSize(window, &w, &h);
    return glm::uvec2(w, h);
}

glm::ivec4 ge::Window::get_frame_size()
{
    int left, top, right, bottom;
    glfwGetWindowFrameSize(window, &left, &top, &right, &bottom);
    return glm::ivec4(left, top, right, bottom);
}

glm::uvec2 ge::Window::get_frame_buffer_size()
{
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    return glm::uvec2(width, height);
}

glm::vec2 ge::Window::get_content_scale()
{
    float x, y;
    glfwGetWindowContentScale(window, &x, &y);
    return glm::vec2(x, y);
}

glm::vec2 ge::Window::get_position()
{
    int x, y;
    glfwGetWindowPos(window, &x, &y);
    return glm::vec2(x, y);
}

GLFWwindow *ge::Window::get_pointer()
{
    return window;
}

std::string ge::Window::get_title()
{
    return std::string(glfwGetWindowTitle(window));
}

void ge::Window::set_icon(const std::string &icon_path)
{
    if(icon_path.empty())
    {
        glfwSetWindowIcon(window, 0, nullptr);
    }
    else
    { //https://www.glfw.org/docs/latest/window_guide.html => Section: Window icon
        glfwSetWindowIcon(window, 1, load_icon)
    }
}

void ge::Window::hint_resizable(bool value)
{
    glfwWindowHint(GLFW_RESIZABLE, value);
}

void ge::Window::hint_visible(bool value)
{
    glfwWindowHint(GLFW_VISIBLE, value);
}

void ge::Window::hint_decorated(bool value)
{
    glfwWindowHint(GLFW_DECORATED, value);
}

void ge::Window::hint_focused(bool value)
{
    glfwWindowHint(GLFW_FOCUSED, value);
}

void ge::Window::hint_auto_iconify(bool value)
{
    glfwWindowHint(GLFW_AUTO_ICONIFY, value);
}

void ge::Window::hint_floating(bool value)
{
    glfwWindowHint(GLFW_FLOATING, value);
}

void ge::Window::hint_maximized(bool value)
{
    glfwWindowHint(GLFW_MAXIMIZED, value);
}

void ge::Window::hint_center_cursor(bool value)
{
    glfwWindowHint(GLFW_CENTER_CURSOR, value);
}

void ge::Window::hint_transparent_framebuffer(bool value)
{
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, value);
}

void ge::Window::hint_focus_on_show(bool value)
{
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, value);
}

void ge::Window::hint_xposition(int x)
{
    glfwWindowHint(GLFW_POSITION_X, x);
}

void ge::Window::hint_yposition(int y)
{
    glfwWindowHint(GLFW_POSITION_Y, y);
}
