#ifndef __GE_KEY_INPUT_HPP__
#define __GE_KEY_INPUT_HPP__
#include <GLFW/glfw3.h>
#include <string>
#include <unordered_map>

#define K(k) GLFW_KEY_##k

namespace ge
{
    enum KeyState
    {
        NoState=-1,
        Realeased=GLFW_RELEASE,
        Pressed=GLFW_PRESS,
        Repeated=GLFW_REPEAT
    };

    class KeyInput
    {
    private:
        static GLFWwindow *window;
        static std::unordered_map<std::string, int> key_map;
        static std::unordered_map<int, KeyState> key_state_map;
    public:
        static void set_window(GLFWwindow *win);
        static int get_scan_code(int key);
        static ge::KeyState get_state(int key);
        static ge::KeyState get_key_state(int key);
        static bool is_pressed(int key);
        static bool is_released(int key);
        static void set_sticky_mode(bool value=true);
        static void set_lock_mode(bool value=true);
        static void set_key_state(int key, KeyState state);
        static std::string get_name(int key);
        static std::unordered_map<std::string, int>& get_key_map();
        static std::unordered_map<int, KeyState>& get_key_state_map();
    };
}

#endif
