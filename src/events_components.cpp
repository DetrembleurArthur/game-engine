#include "events_components.hpp"
#include <log.hpp>
#include <algorithm>
#include <mouse_input.hpp>
#include <application.hpp>

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

void ge::EventsComponent::on_mouse_hover(std::function<void(ge::events::MouseHoverEvent *event)> callback, ge::EventInfos infos)
{
    ge::events::MouseHoverEvent *event = new ge::events::MouseHoverEvent([callback](ge::events::Event *event) {
        callback(dynamic_cast<events::MouseHoverEvent *>(event));
    });
    add_event(event, infos);
}

void ge::EventsComponent::on_mouse_enter(std::function<void(ge::events::MouseEnterEvent *event)> callback, ge::EventInfos infos)
{
    ge::events::MouseEnterEvent *event = new ge::events::MouseEnterEvent([callback](ge::events::Event *event) {
        callback(dynamic_cast<events::MouseEnterEvent *>(event));
    });
    add_event(event, infos);
}

void ge::EventsComponent::on_mouse_leave(std::function<void(ge::events::MouseLeaveEvent *event)> callback, ge::EventInfos infos)
{
    ge::events::MouseLeaveEvent *event = new ge::events::MouseLeaveEvent([callback](ge::events::Event *event) {
        callback(dynamic_cast<events::MouseLeaveEvent *>(event));
    });
    add_event(event, infos);
}
