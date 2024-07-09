#include "ge/utils/log.hpp"

void ge::log(const std::string &msg, LogLevels level)
{
    std::string level_str = "";
    switch(level)
    {
        case LogLevels::INFO:
            level_str = "[INFO]";
            break;
        case LogLevels::WARNING:
            level_str = "[WARNING]";
            break;
        case LogLevels::ERROR:
            level_str = "[ERROR]";
            break;
        case LogLevels::GLFW_ERROR:
            level_str = "[GLFW_ERROR]";
            break;
        case LogLevels::GLOBAL_EVENT:
            level_str = "[GLOBAL_EVENT]";
            break;
        case LogLevels::WIN_EVENT:
            level_str = "[WIN_EVENT]";
            break;
        case LogLevels::KEY_EVENT:
            level_str = "[KEY_EVENT]";
            break;
        case LogLevels::MOUSE_EVENT:
            level_str = "[MOUSE_EVENT]";
            break;
        case LogLevels::CONTROLLER_EVENT:
            level_str = "[CONTROLLER_EVENT]";
            break;
        case LogLevels::CLIPBOARD:
            level_str = "[CLIPBOARD]";
            break;
        case LogLevels::SCENE:
            level_str = "[SCENE]";
            break;
        case LogLevels::SHADER:
            level_str = "[SHADER]";
            break;
        case LogLevels::TEXTURE:
            level_str = "[TEXTURE]";
            break;
        default:
            level_str = "[UNKNOWN]";
    }
    std::cerr << level_str << " " << msg << std::endl;
}