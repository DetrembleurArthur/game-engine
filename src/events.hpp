#ifndef __GE_EVENTS_HPP__
#define __GE_EVENTS_HPP__
#include <game_object.hpp>
#include <functional>

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

        class MouseHoverEvent : public Event
        {
        protected:
            virtual bool is_append(GameObject& go);
        public:
            glm::vec2 mp={0, 0};
            using Event::Event;
            MouseHoverEvent() = default;
        };

        class MouseEnterEvent : public MouseHoverEvent
        {
        protected:
            bool hover=false;
            virtual bool is_append(GameObject& go);
        public:
            using MouseHoverEvent::MouseHoverEvent;
            MouseEnterEvent() = default;
        };

        class MouseLeaveEvent : public MouseHoverEvent
        {
        protected:
            bool hover=false;
            virtual bool is_append(GameObject& go);
        public:
            using MouseHoverEvent::MouseHoverEvent;
            MouseLeaveEvent() = default;
        };
    }
}

#endif
