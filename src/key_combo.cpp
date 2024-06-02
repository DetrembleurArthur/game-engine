#include "key_combo.hpp"

ge::KeyCombo::KeyCombo()
{
}

ge::KeyCombo &ge::KeyCombo::combine(const std::string &keystr)
{
    return combine(KeyInput::get_key_map()[keystr]);
}

ge::KeyCombo &ge::KeyCombo::combine(int key)
{
    keys.push_back(key);
    return *this;
}

ge::KeyState ge::KeyCombo::get_state()
{
    KeyState tmp_state = KeyState::NoState;
    for(int key : keys)
    {
        KeyState key_state = KeyInput::get_key_state(key);
        if(tmp_state == KeyState::NoState)
        {
            tmp_state = key_state;
        }
        if(key_state != tmp_state || key_state == KeyState::NoState)
        {
            reset_state();
            return state;
        }
        tmp_state = key_state;
    }
    if(tmp_state == KeyState::Pressed || tmp_state == KeyState::Repeated)
    {
        pressed = true;
    }
    else if(tmp_state == KeyState::Realeased)
    {
        if(pressed)
        {
            pressed = false;
        }
        else
        {
            tmp_state = KeyState::NoState;
        }
    }
    state = tmp_state;
    return state;
}

void ge::KeyCombo::reset_state()
{
    state = KeyState::NoState;
}

void ge::KeyCombo::on(KeyState state, std::function<void()> c)
{
    if(state > KeyState::NoState)
    {
        callbacks[state] = c;
    }
}

void ge::KeyCombo::run()
{
    KeyState state = get_state();
    if(state > KeyState::NoState)
    {
        const auto& callback = callbacks[state];
        if(callback)
            callback();
    }
}
