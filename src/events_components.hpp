#ifndef __GE_EVENTS_COMPONENT_HPP__
#define __GE_EVENTS_COMPONENT_HPP__
#include <component.hpp>
#include <vector>
#include <events.hpp>

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
    };
}

#endif
