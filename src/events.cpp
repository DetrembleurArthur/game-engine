#include "events.hpp"
#include <application.hpp>
#include <mouse_input.hpp>

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

bool ge::events::MouseHoverEvent::is_append(GameObject& go)
{
    auto& app = ge::Application::get();
    mp = ge::MouseInput::get_position(app.get_scene_manager().get_current()->get_camera());
    return go.get_transform().contains(mp);
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
