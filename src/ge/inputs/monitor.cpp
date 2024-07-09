#include "ge/inputs/monitor.hpp"

ge::Monitor::Monitor(GLFWmonitor *monitor) : monitor(monitor)
{

}

std::vector<GLFWvidmode> ge::Monitor::get_video_modes()
{
    std::vector<GLFWvidmode> video_modes;
    int count;
    const GLFWvidmode *glfw_video_modes = glfwGetVideoModes(monitor, &count);
    if(glfw_video_modes)
    {
        for(int i = 0; i < count; i++)
        {
            video_modes.push_back(glfw_video_modes[i]);
        }
    }
    return video_modes;
}

GLFWvidmode ge::Monitor::get_video_mode()
{
    return *glfwGetVideoMode(monitor);
}

glm::uvec2 ge::Monitor::get_physical_size()
{
    glm::uvec2 size(0, 0);
    int w, h;
    glfwGetMonitorPhysicalSize(monitor, &w, &h);
    size.x = w;
    size.y = h;
    return size;
}

glm::vec2 ge::Monitor::get_content_scale()
{
    glm::vec2 size(0, 0);
    float x, y;
    glfwGetMonitorContentScale(monitor, &x, &y);
    size.x = x;
    size.y = y;
    return size;
}

glm::ivec2 ge::Monitor::get_position()
{
    glm::ivec2 position(0, 0);
    int x, y;
    glfwGetMonitorPos(monitor, &x, &y);
    position.x = x;
    position.y = y;
    return position;
}

glm::ivec4 ge::Monitor::get_work_area()
{
    glm::ivec4 area(0, 0, 0, 0);
    int x, y, w, h;
    glfwGetMonitorWorkarea(monitor, &x, &y, &w, &h);
    area.x = x;
    area.y = y;
    area.z = w;
    area.w = h;
    return area;
}

std::string ge::Monitor::get_name()
{
    return std::string(glfwGetMonitorName(monitor));
}

std::vector<ge::Monitor> ge::Monitor::get_monitors()
{
    std::vector<Monitor> monitors;
    int count;
    GLFWmonitor **glfw_monitors = glfwGetMonitors(&count);
    if(glfw_monitors)
    {
        for(int i = 0; i < count; i++)
        {
            GLFWmonitor *glfw_monitor = glfw_monitors[i];
            monitors.push_back(Monitor(glfw_monitor));
        }
    }
    return monitors;
}

ge::Monitor ge::Monitor::get_primary_monitor()
{
    return Monitor(glfwGetPrimaryMonitor());
}

GLFWmonitor *ge::Monitor::get_pointer()
{
    return monitor;
}
