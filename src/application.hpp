#ifndef __GE_APPLICATION_HPP__
#define __GE_APPLICATION_HPP__
#include <iostream>
#include <window.hpp>
#include <global_events.hpp>


namespace ge
{
    class Application
    {
    private:
        static Application *app;
        bool initialized=false;
        ge::Window *window=nullptr;
        void (*hint_callback)();
    public:
        Application(void (*hint_callback)()=[](){ge::log("default hints");});
        ~Application();
        void init(const std::string& title="Untitled", unsigned width=640, unsigned height=480);
        void run();
        bool is_initialized() const;
        ge::Window& get_window();
        static Application& get();
    };
}

#endif
