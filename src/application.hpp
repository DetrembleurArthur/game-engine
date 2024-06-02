#ifndef __GE_APPLICATION_HPP__
#define __GE_APPLICATION_HPP__
#include <iostream>
#include <window.hpp>
#include <global_events.hpp>
#include <key_input.hpp>
#include <mouse_input.hpp>
#include <controller_events.hpp>

namespace ge
{
    class Application
    {
    private:
        static Application *app;
        bool initialized=false;
        ge::Window *window=nullptr;
        void (*events_policy_callback)()=glfwPollEvents;
        void (*hint_callback)();
    public:
        Application(void (*hint_callback)()=[](){ge::log("default hints");});
        ~Application();
        void init(const std::string& title="Untitled", unsigned width=640, unsigned height=480);
        void run();
        bool is_initialized() const;
        void poll_events_policy();
        void wait_events_policy();
        void post_empty_event();
        ge::Window& get_window();
        static Application& get();
    };
}

#endif
