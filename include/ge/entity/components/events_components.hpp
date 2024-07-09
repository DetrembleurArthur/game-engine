#ifndef __GE_EVENTS_COMPONENT_HPP__
#define __GE_EVENTS_COMPONENT_HPP__
#include <ge/entity/components/component.hpp>
#include <vector>
#include <ge/entity/components/events/events.hpp>

namespace ge
{
    

    namespace events
    {
        
    }

    struct EventInfos
    {
        int priority=0;
    };

    class EventsComponent : public UpdatableComponent
    {
    private:
        std::vector<std::pair<ge::events::Event*, ge::EventInfos>> events;
    public:
        using UpdatableComponent::UpdatableComponent;
        ~EventsComponent();
        virtual void update(float dt) override;
        void add_event(ge::events::Event *event, ge::EventInfos infos={.priority=0});
        template <typename T> void remove_event()
        {
            for(auto& pair : events)
            {
                if(typeid(*pair.first) == typeid(T))
                    pair.first->remove();
            }
        }
        void on_mouse_hover(std::function<void(ge::events::MouseHoverEvent *event)> callback, ge::EventInfos infos={.priority=0});
        void on_mouse_enter(std::function<void(ge::events::MouseEnterEvent *event)> callback, ge::EventInfos infos={.priority=0});
        void on_mouse_leave(std::function<void(ge::events::MouseLeaveEvent *event)> callback, ge::EventInfos infos={.priority=0});
    };
}

#endif