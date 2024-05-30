#include "global_events.hpp"

void (*ge::GlobalEvents::on_monitor_connected_callback)(ge::Monitor& monitor)=nullptr;
void (*ge::GlobalEvents::on_monitor_disconnected_callback)(ge::Monitor& monitor)=nullptr;

void ge::GlobalEvents::init()
{
    glfwSetMonitorCallback([](GLFWmonitor *glfw_monitor, int event){
        Monitor monitor(glfw_monitor);
        switch(event)
        {
            case GLFW_CONNECTED:
                ge::log("monitor '" + monitor.get_name() + "' connected", ge::LogLevels::GLOBAL_EVENT);
                if(ge::GlobalEvents::on_monitor_connected_callback)
                    ge::GlobalEvents::on_monitor_connected_callback(monitor);
                break;
            case GLFW_DISCONNECTED:
                ge::log("monitor '" + monitor.get_name() + "' disconnected", ge::LogLevels::GLOBAL_EVENT);
                if(ge::GlobalEvents::on_monitor_disconnected_callback)
                    ge::GlobalEvents::on_monitor_disconnected_callback(monitor);
                break;
            default:
                ge::log("unknown monitor event: " + std::to_string(event), ge::LogLevels::GLOBAL_EVENT);
        }
    });
}

void ge::GlobalEvents::error_callback(void (*callback)(int, const char *))
{
    glfwSetErrorCallback(callback);
}

void ge::GlobalEvents::on_monitor_connected(void (*c)(Monitor &monitor))
{
    GlobalEvents::on_monitor_connected_callback = c;
}

void ge::GlobalEvents::on_monitor_disconnected(void (*c)(Monitor &monitor))
{
    GlobalEvents::on_monitor_disconnected_callback = c;
}
