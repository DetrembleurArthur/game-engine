#ifndef __GE_LOG_HPP__
#define __GE_LOG_HPP__

#include <iostream>
#include <string>

namespace ge
{
    enum LogLevels
    {
        INFO,
        WARNING,
        ERROR,
        GLFW_ERROR,
        GLOBAL_EVENT,
        WIN_EVENT,
        KEY_EVENT,
        MOUSE_EVENT,
        CONTROLLER_EVENT,
        CLIPBOARD,
        SCENE,
        SHADER,
        TEXTURE
    };

    void log(const std::string& msg, LogLevels level=LogLevels::INFO);
}
#endif
