#ifndef __GE_GLOBAL_EVENTS_HPP__
#define __GE_GLOBAL_EVENTS_HPP__

#include <ge/inputs/monitor.hpp>

namespace ge
{
    class GlobalEvents
    {
    private:
        static void (*on_monitor_connected_callback)(Monitor& monitor);
        static void (*on_monitor_disconnected_callback)(Monitor& monitor);
    public:
        static void init();
        static void error_callback(void(*callback)(int, const char *));
        static void on_monitor_connected(void (*c)(Monitor& monitor));
        static void on_monitor_disconnected(void (*c)(Monitor& monitor));
    };
}

#endif
