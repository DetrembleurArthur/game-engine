#ifndef __GE_KEY_COMBO_HPP__
#define __GE_KEY_COMBO_HPP__
#include <ge/inputs/key_input.hpp>
#include <vector>
#include <functional>

namespace ge
{
    class KeyCombo
    {
    private:
        std::vector<int> keys;
        KeyState state=KeyState::NoState;
        bool pressed=false;
        std::function<void()> callbacks[3];
    public:
        KeyCombo();
        KeyCombo& combine(const std::string& keystr);
        KeyCombo& combine(int key);
        KeyState get_state();
        void reset_state();
        ge::KeyCombo& on(KeyState state, std::function<void()> c);
        ge::KeyCombo& on_pressed(std::function<void()> c);
        ge::KeyCombo& on_released(std::function<void()> c);
        ge::KeyCombo& on_repeated(std::function<void()> c);
        void run();
        bool is_pressed(bool continuous=false);
        bool is_released();
        bool is_repeated();
    };
}

#endif
