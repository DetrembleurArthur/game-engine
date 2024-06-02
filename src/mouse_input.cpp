#include "mouse_input.hpp"

GLFWwindow * ge::MouseInput::window = nullptr;
GLFWcursor *ge::MouseInput::cursor = nullptr;
std::unordered_map<std::string, int> ge::MouseInput::button_map = {
    {"right", GLFW_MOUSE_BUTTON_RIGHT},
    {"left", GLFW_MOUSE_BUTTON_LEFT},
    {"middle", GLFW_MOUSE_BUTTON_MIDDLE}
};

void ge::MouseInput::set_window(GLFWwindow *window)
{
    MouseInput::window = window;
}

glm::vec2 ge::MouseInput::get_position()
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return glm::vec2(x, y);
}

void ge::MouseInput::hide()
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void ge::MouseInput::lock()
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void ge::MouseInput::captured()
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
}

void ge::MouseInput::destroy_cursor()
{
    if(MouseInput::cursor)
    {
        glfwDestroyCursor(MouseInput::cursor);
        MouseInput::cursor = nullptr;
    }
}

void ge::MouseInput::set_as_cursor(ge::Image &image)
{
    destroy_cursor();
    MouseInput::cursor = glfwCreateCursor(&image.get(), 0, 0);
    glfwSetCursor(MouseInput::window, MouseInput::cursor);
}

void ge::MouseInput::set_as_cursor(ge::Cursors cursor_id)
{
    destroy_cursor();
    if(cursor_id != ge::Cursors::DEFAULT)
        MouseInput::cursor = glfwCreateStandardCursor(static_cast<int>(cursor_id));
    glfwSetCursor(MouseInput::window, MouseInput::cursor);
}

void ge::MouseInput::set_sticky(bool value)
{
    glfwSetInputMode(MouseInput::window, GLFW_STICKY_MOUSE_BUTTONS, value);
}

bool ge::MouseInput::hovered()
{
    return glfwGetWindowAttrib(MouseInput::window, GLFW_HOVERED);
}

ge::ButtonState ge::MouseInput::get_state(int btn)
{
    return static_cast<ge::ButtonState>(glfwGetMouseButton(MouseInput::window, btn));
}

ge::ButtonState ge::MouseInput::get_state(const std::string &btn)
{
    return MouseInput::get_state(MouseInput::button_map[btn]);
}

void ge::MouseInput::normal()
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
