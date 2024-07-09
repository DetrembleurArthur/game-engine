#include "ge/inputs/key_events.hpp"
#include <ge/inputs/key_input.hpp>
#include <ge/utils/log.hpp>
#include <codecvt>
#include <locale>

std::function<void(int key, int scancode, int action, int mods)> ge::KeyEvents::on_key_callback;
std::function<void(std::string)> ge::KeyEvents::on_character_callback;
std::vector<ge::KeyCombo> ge::KeyEvents::key_combos;

void ge::KeyEvents::set_on_key(GLFWwindow *win, int key, int scancode, int action, int mods)
{
    log("key-" + std::string(action == GLFW_PRESS ? "pressed" : (action == GLFW_RELEASE ? "released" : "repeated")) + ": key=" + std::to_string(key) + " scancode=" + std::to_string(scancode), LogLevels::KEY_EVENT);
    KeyInput::set_key_state(key, static_cast<KeyState>(action));
    for(KeyCombo& kc : KeyEvents::key_combos)
    {
        kc.run();
    }
    if(KeyEvents::on_key_callback)
    {
        KeyEvents::on_key_callback(key, scancode, action, mods);
    }
}

void ge::KeyEvents::set_on_character(GLFWwindow *win, unsigned codepoint)
{
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
    std::string utf8 = convert.to_bytes(codepoint);
    log("character: " + utf8, LogLevels::KEY_EVENT);
    if(KeyEvents::on_character_callback)
    {
        KeyEvents::on_character_callback(utf8);
    }
}

void ge::KeyEvents::init(GLFWwindow *window)
{
    glfwSetKeyCallback(window, ge::KeyEvents::set_on_key);
    glfwSetCharCallback(window, ge::KeyEvents::set_on_character);
}

void ge::KeyEvents::on_key(std::function<void(int key, int scancode, int action, int mods)> c)
{
    KeyEvents::on_key_callback = c;
}

void ge::KeyEvents::on_character(std::function<void(std::string)> c)
{
    KeyEvents::on_character_callback = c;
}

void ge::KeyEvents::add_combo(const KeyCombo &kc)
{
    KeyEvents::key_combos.push_back(kc);
}
