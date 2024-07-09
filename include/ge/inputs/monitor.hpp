#ifndef __GE_MONITOR_HPP__
#define __GE_MONITOR_HPP__
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <glm/glm.hpp>

namespace ge
{
    class Monitor
    {
    private:
        GLFWmonitor *monitor;
    public:
        Monitor(GLFWmonitor *monitor);
        std::vector<GLFWvidmode> get_video_modes();
        GLFWvidmode get_video_mode();
        glm::uvec2 get_physical_size();
        glm::vec2 get_content_scale();
        glm::ivec2 get_position();
        glm::ivec4 get_work_area();
        std::string get_name();
        static std::vector<Monitor> get_monitors();
        static Monitor get_primary_monitor();
        GLFWmonitor *get_pointer();
    };
}

#endif
