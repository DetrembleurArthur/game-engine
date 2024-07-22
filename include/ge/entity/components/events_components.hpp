#ifndef __GE_EVENTS_COMPONENT_HPP__
#define __GE_EVENTS_COMPONENT_HPP__
#include <ge/entity/components/component.hpp>
#include <vector>
#include <ge/entity/components/events/events.hpp>

namespace ge
{
    struct EventInfos
    {
        int priority=0;
    };

    enum DragMode
    {
        TWO_AXIS,
        X_AXIS,
        Y_AXIS
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
        ge::events::MouseHoverEvent& on_mouse_hover(std::function<void(ge::events::MouseHoverEvent *event)> callback, ge::EventInfos infos={.priority=0});
        ge::events::MouseEnterEvent& on_mouse_enter(std::function<void(ge::events::MouseEnterEvent *event)> callback, ge::EventInfos infos={.priority=0});
        ge::events::MouseLeaveEvent& on_mouse_leave(std::function<void(ge::events::MouseLeaveEvent *event)> callback, ge::EventInfos infos={.priority=0});
        ge::events::MouseClickEvent& on_mouse_click(std::function<void(ge::events::MouseClickEvent *event)> callback, ge::EventInfos infos={.priority=0});
        ge::events::MouseLeftClickEvent& on_mouse_left_clicked(std::function<void(ge::events::MouseLeftClickEvent *event)> callback, ge::EventInfos infos={.priority=0});
        ge::events::MouseLeftPressedEvent& on_mouse_left_pressed(std::function<void(ge::events::MouseLeftPressedEvent *event)> callback, ge::EventInfos infos={.priority=0});
        ge::events::MouseLeftReleaseEvent& on_mouse_left_release(std::function<void(ge::events::MouseLeftReleaseEvent *event)> callback, ge::EventInfos infos={.priority=0});
        ge::events::MouseRightClickEvent& on_mouse_right_clicked(std::function<void(ge::events::MouseRightClickEvent *event)> callback, ge::EventInfos infos={.priority=0});
        ge::events::MouseRightPressedEvent& on_mouse_right_pressed(std::function<void(ge::events::MouseRightPressedEvent *event)> callback, ge::EventInfos infos={.priority=0});
        ge::events::MouseRightReleaseEvent& on_mouse_right_release(std::function<void(ge::events::MouseRightReleaseEvent *event)> callback, ge::EventInfos infos={.priority=0});
        ge::events::MouseMiddleClickEvent& on_mouse_middle_clicked(std::function<void(ge::events::MouseMiddleClickEvent *event)> callback, ge::EventInfos infos={.priority=0});
        ge::events::MouseMiddlePressedEvent& on_mouse_middle_pressed(std::function<void(ge::events::MouseMiddlePressedEvent *event)> callback, ge::EventInfos infos={.priority=0});
        ge::events::MouseMiddleReleaseEvent& on_mouse_middle_release(std::function<void(ge::events::MouseMiddleReleaseEvent *event)> callback, ge::EventInfos infos={.priority=0});
        ge::events::MouseDragEvent& on_mouse_drag(std::function<void(ge::events::MouseDragEvent *event)> callback, ge::EventInfos infos={.priority=0});
        ge::events::MouseDragEvent& dragging(DragMode mode=DragMode::TWO_AXIS, bool use_properties=false);
    };
}

#endif
