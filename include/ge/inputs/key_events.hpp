#ifndef __GE_KEY_EVENTS_HPP__
#define __GE_KEY_EVENTS_HPP__
#include <functional>
#include <ge/inputs/key_combo.hpp>

namespace ge
{
    class KeyEvents
    {
    private:
        static std::function<void(int key, int scancode, int action, int mods)> on_key_callback;
        static std::function<void(std::string c)> on_character_callback;
        static std::vector<KeyCombo> key_combos;
        static void set_on_key(GLFWwindow *win, int key, int scancode, int action, int mods);
        static void set_on_character(GLFWwindow *win, unsigned codepoint);
    public:
        static void init(GLFWwindow *window);
        static void on_key(std::function<void(int key, int scancode, int action, int mods)> c);
        static void on_character(std::function<void(std::string)> c);
        static void add_combo(const KeyCombo& kc);
    };
}

#endif
