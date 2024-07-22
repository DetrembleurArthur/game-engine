#ifndef __GE_EVENTS_HPP__
#define __GE_EVENTS_HPP__
#include <ge/entity/game_object.hpp>
#include <functional>
#include <ge/inputs/mouse_input.hpp>

namespace ge
{
    namespace events
    {
        class Event
        {
        private:
            std::function<void(Event*)> callback;
            bool to_remove=false;
        protected:
            virtual bool is_append(GameObject& go);
        public:
            Event() = default;
            Event(std::function<void(Event*)> callback);
            void run(GameObject& go);
            bool is_to_remove() const;
            void remove();
        };

        /* mouse hovering the object */
        class MouseHoverEvent : public Event
        {
        protected:
            bool use_collider_flag=false;
            virtual bool is_append(GameObject& go);
        public:
            glm::vec2 mp={0, 0};
            using Event::Event;
            MouseHoverEvent() = default;
            MouseHoverEvent& use_collider();
        };
         /* mouse enter the object */
        class MouseEnterEvent : public MouseHoverEvent
        {
        protected:
            bool hover=false;
            virtual bool is_append(GameObject& go);
        public:
            using MouseHoverEvent::MouseHoverEvent;
            MouseEnterEvent() = default;
        };

        /* mouse leaving the object */
        class MouseLeaveEvent : public MouseHoverEvent
        {
        protected:
            bool hover=false;
            virtual bool is_append(GameObject& go);
        public:
            using MouseHoverEvent::MouseHoverEvent;
            MouseLeaveEvent() = default;
        };

        /* mouse click in the object */
        class MouseClickEvent : public MouseHoverEvent
        {
        protected:
            bool click_oob=false;
            bool actioned=false;
            int btn=-1;//any
            bool continuous=true;
            ge::ButtonState state=ge::ButtonState::PressedBtn;
            virtual bool is_append(GameObject& go);
        public:
            using MouseHoverEvent::MouseHoverEvent;
            MouseClickEvent(int btn, bool continuous, ge::ButtonState state, std::function<void(Event*)> callback);
            MouseClickEvent() = default;
        };

        class MouseLeftClickEvent : public MouseClickEvent
        {
        public:
            MouseLeftClickEvent(std::function<void(Event*)> callback);
        };

        class MouseLeftPressedEvent : public MouseClickEvent
        {
        public:
            MouseLeftPressedEvent(std::function<void(Event*)> callback);
        };

        class MouseLeftReleaseEvent : public MouseClickEvent
        {
        public:
            MouseLeftReleaseEvent(std::function<void(Event*)> callback);
        };


        class MouseRightClickEvent : public MouseClickEvent
        {
        public:
            MouseRightClickEvent(std::function<void(Event*)> callback);
        };

        class MouseRightPressedEvent : public MouseClickEvent
        {
        public:
            MouseRightPressedEvent(std::function<void(Event*)> callback);
        };

        class MouseRightReleaseEvent : public MouseClickEvent
        {
        public:
            MouseRightReleaseEvent(std::function<void(Event*)> callback);
        };


        class MouseMiddleClickEvent : public MouseClickEvent
        {
        public:
            MouseMiddleClickEvent(std::function<void(Event*)> callback);
        };

        class MouseMiddlePressedEvent : public MouseClickEvent
        {
        public:
            MouseMiddlePressedEvent(std::function<void(Event*)> callback);
        };

        class MouseMiddleReleaseEvent : public MouseClickEvent
        {
        public:
            MouseMiddleReleaseEvent(std::function<void(Event*)> callback);
        };

        class MouseDragEvent : public MouseLeftClickEvent
        {
        protected:
            bool dragging=false;
            virtual bool is_append(GameObject& go);
        public:
            using MouseLeftClickEvent::MouseLeftClickEvent;
            MouseDragEvent() = default;
            glm::vec2 delta=glm::vec2(0, 0);
            glm::vec2 dragged_position=glm::vec2(0, 0);
        };
    }
}

#endif
