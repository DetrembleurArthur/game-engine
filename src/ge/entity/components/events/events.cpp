#include "ge/entity/components/events/events.hpp"
#include <ge/core/application.hpp>
#include <ge/entity/components/collider_component.hpp>


bool ge::events::Event::is_append(GameObject& go)
{
    return false;
}

ge::events::Event::Event(std::function<void(Event *)> callback) : callback(callback)
{
}

void ge::events::Event::run(GameObject& go)
{
    if(is_append(go))
    {
        callback(this);
        log("event " + std::string(typeid(*this).name()) + " triggered");
    }
}

bool ge::events::Event::is_to_remove() const
{
    return to_remove;
}

void ge::events::Event::remove()
{
    to_remove = true;
    log("event " + std::string(typeid(*this).name()) + " waiting to be removed");
}

/* EVENTS DEFINITIONS */



bool ge::events::MouseHoverEvent::is_append(GameObject& go)
{
    auto& app = ge::Application::get();
    mp = ge::MouseInput::get_position(app.get_scene_manager().get_current()->get_camera());
    return use_collider_flag ? go.get_component<ge::ColliderComponent>().contains(mp) : go.get_transform().contains(mp);
}

ge::events::MouseHoverEvent &ge::events::MouseHoverEvent::use_collider()
{
    use_collider_flag = !use_collider_flag;
    return *this;
}

bool ge::events::MouseEnterEvent::is_append(GameObject &go)
{
    if(ge::events::MouseHoverEvent::is_append(go))
    {
        if(!hover)
        {
            hover = true;
            return true;
        }
        return false;
    }
    hover = false;
    return false;
}

bool ge::events::MouseLeaveEvent::is_append(GameObject &go)
{
    if(ge::events::MouseHoverEvent::is_append(go))
    {
        hover = true;
        return false;
    }
    if(hover)
    {
        hover = false;
        return true;
    }
    return false;
}

ge::events::MouseClickEvent::MouseClickEvent(int btn, bool continuous, ge::ButtonState state, std::function<void(Event *)> callback) :
 MouseHoverEvent(callback), btn(btn), state(state), continuous(continuous)
{
}

bool ge::events::MouseClickEvent::is_append(GameObject &go)
{
    bool cond=btn < 0 ? ge::MouseInput::is_any_button(state) : ge::MouseInput::is_button(btn, state);
    if(ge::events::MouseHoverEvent::is_append(go) && !click_oob)
    {
        if(continuous)
            return cond;
        if(cond)
        {
            if(!actioned)
            {
                actioned = true;
                return cond;
            }
        }
        else
        {
            actioned = false;
        }
    }
    else if(cond && !click_oob)
    {
        click_oob = true;
    }
    else if(!cond && click_oob)
    {
        click_oob = false;
    }
    return false;
}

ge::events::MouseLeftClickEvent::MouseLeftClickEvent(std::function<void(Event *)> callback) : MouseClickEvent(GLFW_MOUSE_BUTTON_LEFT, true, ge::ButtonState::PressedBtn, callback)
{
}

ge::events::MouseLeftPressedEvent::MouseLeftPressedEvent(std::function<void(Event *)> callback) : MouseClickEvent(GLFW_MOUSE_BUTTON_LEFT, false, ge::ButtonState::PressedBtn, callback)
{
}

ge::events::MouseLeftReleaseEvent::MouseLeftReleaseEvent(std::function<void(Event *)> callback) : MouseClickEvent(GLFW_MOUSE_BUTTON_LEFT, false, ge::ButtonState::ReleasedBtn, callback)
{
}


ge::events::MouseRightClickEvent::MouseRightClickEvent(std::function<void(Event *)> callback) : MouseClickEvent(GLFW_MOUSE_BUTTON_RIGHT, true, ge::ButtonState::PressedBtn, callback)
{
}

ge::events::MouseRightPressedEvent::MouseRightPressedEvent(std::function<void(Event *)> callback) : MouseClickEvent(GLFW_MOUSE_BUTTON_RIGHT, false, ge::ButtonState::PressedBtn, callback)
{
}

ge::events::MouseRightReleaseEvent::MouseRightReleaseEvent(std::function<void(Event *)> callback) : MouseClickEvent(GLFW_MOUSE_BUTTON_RIGHT, false, ge::ButtonState::ReleasedBtn, callback)
{
}


ge::events::MouseMiddleClickEvent::MouseMiddleClickEvent(std::function<void(Event *)> callback) : MouseClickEvent(GLFW_MOUSE_BUTTON_MIDDLE, true, ge::ButtonState::PressedBtn, callback)
{
}

ge::events::MouseMiddlePressedEvent::MouseMiddlePressedEvent(std::function<void(Event *)> callback) : MouseClickEvent(GLFW_MOUSE_BUTTON_MIDDLE, false, ge::ButtonState::PressedBtn, callback)
{
}

ge::events::MouseMiddleReleaseEvent::MouseMiddleReleaseEvent(std::function<void(Event *)> callback) : MouseClickEvent(GLFW_MOUSE_BUTTON_MIDDLE, false, ge::ButtonState::ReleasedBtn, callback)
{
}


bool ge::events::MouseDragEvent::is_append(GameObject &go)
{
    if(ge::events::MouseLeftClickEvent::is_append(go) || (dragging && ge::MouseInput::is_left_button()))
    {
        if(!dragging)
        {
            dragging = true;
            delta = mp - go.get_transform().get_position();
        }
        dragged_position = mp - delta;
        return true;
    }
    else
    {
        dragging = false;
    }
    return false;
}
