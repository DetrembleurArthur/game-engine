#ifndef __GE_MOUSE_INPUT_HPP__
#define __GE_MOUSE_INPUT_HPP__
#include <glm/glm.hpp>
#include <ge/graphics/camera2D.hpp>
#include <ge/graphics/image.hpp>
#include <unordered_map>

namespace ge
{
    enum Cursors
    {
        DEFAULT=0,
        ARROW=GLFW_ARROW_CURSOR,
        POINTING_HAND=GLFW_POINTING_HAND_CURSOR,
        IBEAM=GLFW_IBEAM_CURSOR,
        CROSSAIR=GLFW_CROSSHAIR_CURSOR,
        HRESIZE=GLFW_RESIZE_EW_CURSOR,
        VRESIZE=GLFW_RESIZE_NS_CURSOR,
        RESIZE_NWSE=GLFW_RESIZE_NWSE_CURSOR,
        RESIZE_NESW=GLFW_RESIZE_NESW_CURSOR,
        RESIZE_ALL=GLFW_RESIZE_ALL_CURSOR,
        NOT_ALLOWED=GLFW_NOT_ALLOWED_CURSOR
    };

    enum ButtonState
    {
        NoStateBtn=-1,
        ReleasedBtn=GLFW_RELEASE,
        PressedBtn=GLFW_PRESS
    };

    class MouseInput
    {
    private:
        static GLFWwindow *window;
        static GLFWcursor *cursor;
        static std::unordered_map<std::string, int> button_map;
    public:
        static void set_window(GLFWwindow *window);
        static glm::vec2 get_position();
        static glm::vec2 get_position(Camera2D& camera);
        static glm::vec2 get_position(Camera2D* camera);
        static void hide();
        static void lock();
        static void normal();
        static void captured();
        static void destroy_cursor();
        static void set_as_cursor(ge::Image& image);
        static void set_as_cursor(ge::Cursors cursor_id);
        static void set_sticky(bool value=true);
        static bool hovered();
        static ge::ButtonState get_state(int btn);
        static ge::ButtonState get_state(const std::string& btn);
        static bool is_button(int btn, ge::ButtonState state=ge::ButtonState::PressedBtn);
        static bool is_left_button(ge::ButtonState state=ge::ButtonState::PressedBtn);
        static bool is_right_button(ge::ButtonState state=ge::ButtonState::PressedBtn);
        static bool is_middle_button(ge::ButtonState state=ge::ButtonState::PressedBtn);
        static bool is_any_button(ge::ButtonState state=ge::ButtonState::PressedBtn);
    };
}

#endif
