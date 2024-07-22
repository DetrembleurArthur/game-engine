#include "ge/entity/components/events_components.hpp"
#include <ge/utils/log.hpp>
#include <algorithm>
#include <ge/inputs/mouse_input.hpp>
#include <ge/core/application.hpp>
#include <ge/entity/components/shape_properties_component.hpp>

ge::EventsComponent::~EventsComponent()
{
    for(auto& event_pair : events)
    {
        delete event_pair.first;
        log("event cleared");
    }
}

void ge::EventsComponent::update(float dt)
{
    bool clean_activated=false;
    for(auto& event_pair : events)
    {
        event_pair.first->run(*owner);
        if(event_pair.first->is_to_remove())
            clean_activated = true;
    }
    if(clean_activated)
    {
        auto it = std::remove_if(events.begin(), events.end(), [](std::pair<ge::events::Event*, ge::EventInfos>& event_pair) {
            if(event_pair.first->is_to_remove())
            {
                log("event " + std::string(typeid(*event_pair.first).name()) + " removed");
                delete event_pair.first;
                return true;
            }
            return false;
        });
        events.erase(it, events.end());
    }
}

void ge::EventsComponent::add_event(ge::events::Event* event, ge::EventInfos infos)
{
    for(auto& pair : events)
    {
        if(typeid(*pair.first) == typeid(*event))
        {
            log("one event of the same type at a time: " + std::string(typeid(event).name()), ge::LogLevels::ERROR);
            return;
        }
    }
    std::pair<ge::events::Event*, ge::EventInfos> event_pair(event, infos);
    events.push_back(event_pair);
    std::sort(events.begin(), events.end(), [](std::pair<ge::events::Event*, ge::EventInfos>& e1, std::pair<ge::events::Event*, ge::EventInfos>& e2) {
        return e1.second.priority < e2.second.priority;
    });
}

ge::events::MouseHoverEvent& ge::EventsComponent::on_mouse_hover(std::function<void(ge::events::MouseHoverEvent *event)> callback, ge::EventInfos infos)
{
    ge::events::MouseHoverEvent *event = new ge::events::MouseHoverEvent([callback](ge::events::Event *event) {
        callback(dynamic_cast<events::MouseHoverEvent *>(event));
    });
    add_event(event, infos);
    return *event;
}

ge::events::MouseEnterEvent& ge::EventsComponent::on_mouse_enter(std::function<void(ge::events::MouseEnterEvent *event)> callback, ge::EventInfos infos)
{
    ge::events::MouseEnterEvent *event = new ge::events::MouseEnterEvent([callback](ge::events::Event *event) {
        callback(dynamic_cast<events::MouseEnterEvent *>(event));
    });
    add_event(event, infos);
    return *event;
}

ge::events::MouseLeaveEvent& ge::EventsComponent::on_mouse_leave(std::function<void(ge::events::MouseLeaveEvent *event)> callback, ge::EventInfos infos)
{
    ge::events::MouseLeaveEvent *event = new ge::events::MouseLeaveEvent([callback](ge::events::Event *event) {
        callback(dynamic_cast<events::MouseLeaveEvent *>(event));
    });
    add_event(event, infos);
    return *event;
}

ge::events::MouseClickEvent& ge::EventsComponent::on_mouse_click(std::function<void(ge::events::MouseClickEvent *event)> callback, ge::EventInfos infos)
{
    ge::events::MouseClickEvent *event = new ge::events::MouseClickEvent(-1, true, ge::ButtonState::PressedBtn, [callback](ge::events::Event *event) {
        callback(dynamic_cast<events::MouseClickEvent *>(event));
    });
    add_event(event, infos);
    return *event;
}

ge::events::MouseLeftClickEvent& ge::EventsComponent::on_mouse_left_clicked(std::function<void(ge::events::MouseLeftClickEvent *event)> callback, ge::EventInfos infos)
{
    ge::events::MouseLeftClickEvent *event = new ge::events::MouseLeftClickEvent([callback](ge::events::Event *event) {
        callback(dynamic_cast<events::MouseLeftClickEvent *>(event));
    });
    add_event(event, infos);
    return *event;
}

ge::events::MouseLeftPressedEvent& ge::EventsComponent::on_mouse_left_pressed(std::function<void(ge::events::MouseLeftPressedEvent *event)> callback, ge::EventInfos infos)
{
    ge::events::MouseLeftPressedEvent *event = new ge::events::MouseLeftPressedEvent([callback](ge::events::Event *event) {
        callback(dynamic_cast<events::MouseLeftPressedEvent *>(event));
    });
    add_event(event, infos);
    return *event;
}

ge::events::MouseLeftReleaseEvent& ge::EventsComponent::on_mouse_left_release(std::function<void(ge::events::MouseLeftReleaseEvent *event)> callback, ge::EventInfos infos)
{
    ge::events::MouseLeftReleaseEvent *event = new ge::events::MouseLeftReleaseEvent([callback](ge::events::Event *event) {
        callback(dynamic_cast<events::MouseLeftReleaseEvent *>(event));
    });
    add_event(event, infos);
    return *event;
}

ge::events::MouseRightClickEvent& ge::EventsComponent::on_mouse_right_clicked(std::function<void(ge::events::MouseRightClickEvent *event)> callback, ge::EventInfos infos)
{
    ge::events::MouseRightClickEvent *event = new ge::events::MouseRightClickEvent([callback](ge::events::Event *event) {
        callback(dynamic_cast<events::MouseRightClickEvent *>(event));
    });
    add_event(event, infos);
    return *event;
}

ge::events::MouseRightPressedEvent& ge::EventsComponent::on_mouse_right_pressed(std::function<void(ge::events::MouseRightPressedEvent *event)> callback, ge::EventInfos infos)
{
    ge::events::MouseRightPressedEvent *event = new ge::events::MouseRightPressedEvent([callback](ge::events::Event *event) {
        callback(dynamic_cast<events::MouseRightPressedEvent *>(event));
    });
    add_event(event, infos);
    return *event;
}

ge::events::MouseRightReleaseEvent& ge::EventsComponent::on_mouse_right_release(std::function<void(ge::events::MouseRightReleaseEvent *event)> callback, ge::EventInfos infos)
{
    ge::events::MouseRightReleaseEvent *event = new ge::events::MouseRightReleaseEvent([callback](ge::events::Event *event) {
        callback(dynamic_cast<events::MouseRightReleaseEvent *>(event));
    });
    add_event(event, infos);
    return *event;
}

ge::events::MouseMiddleClickEvent& ge::EventsComponent::on_mouse_middle_clicked(std::function<void(ge::events::MouseMiddleClickEvent *event)> callback, ge::EventInfos infos)
{
    ge::events::MouseMiddleClickEvent *event = new ge::events::MouseMiddleClickEvent([callback](ge::events::Event *event) {
        callback(dynamic_cast<events::MouseMiddleClickEvent *>(event));
    });
    add_event(event, infos);
    return *event;
}

ge::events::MouseMiddlePressedEvent& ge::EventsComponent::on_mouse_middle_pressed(std::function<void(ge::events::MouseMiddlePressedEvent *event)> callback, ge::EventInfos infos)
{
    ge::events::MouseMiddlePressedEvent *event = new ge::events::MouseMiddlePressedEvent([callback](ge::events::Event *event) {
        callback(dynamic_cast<events::MouseMiddlePressedEvent *>(event));
    });
    add_event(event, infos);
    return *event;
}

ge::events::MouseMiddleReleaseEvent& ge::EventsComponent::on_mouse_middle_release(std::function<void(ge::events::MouseMiddleReleaseEvent *event)> callback, ge::EventInfos infos)
{
    ge::events::MouseMiddleReleaseEvent *event = new ge::events::MouseMiddleReleaseEvent([callback](ge::events::Event *event) {
        callback(dynamic_cast<events::MouseMiddleReleaseEvent *>(event));
    });
    add_event(event, infos);
    return *event;
}

ge::events::MouseDragEvent& ge::EventsComponent::on_mouse_drag(std::function<void(ge::events::MouseDragEvent *event)> callback, ge::EventInfos infos)
{
    ge::events::MouseDragEvent *event = new ge::events::MouseDragEvent([callback](ge::events::Event *event) {
        callback(dynamic_cast<events::MouseDragEvent *>(event));
    });
    add_event(event, infos);
    return *event;
}

ge::events::MouseDragEvent& ge::EventsComponent::dragging(DragMode mode, bool use_properties)
{
    switch(mode)
    {   
        case DragMode::X_AXIS:
            if(use_properties)
                return on_mouse_drag([this](ge::events::MouseDragEvent *event) {
                    owner->get_component<ge::ShapePropertiesComponent>().x().set(event->dragged_position.x);});
            else
                return on_mouse_drag([this](ge::events::MouseDragEvent *event) {
                    owner->get_transform().set_x(event->dragged_position.x);});
            break;

        case DragMode::Y_AXIS:
            if(use_properties)
                return on_mouse_drag([this](ge::events::MouseDragEvent *event) {
                    owner->get_component<ge::ShapePropertiesComponent>().y().set(event->dragged_position.y);});
            else
                return on_mouse_drag([this](ge::events::MouseDragEvent *event) {
                    owner->get_transform().set_y(event->dragged_position.y);});
            break;
        
        case DragMode::TWO_AXIS:
        default:
            if(use_properties)
                return on_mouse_drag([this](ge::events::MouseDragEvent *event) {
                    owner->get_component<ge::ShapePropertiesComponent>().position().set(event->dragged_position);});
            else
                return on_mouse_drag([this](ge::events::MouseDragEvent *event) {
                    owner->get_transform().set_position(event->dragged_position);});
            break;
    }
}
