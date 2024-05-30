#include "log.hpp"

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
        default:
            level_str = "[UNKNOWN]";
    }
    std::cerr << level_str << " " << msg << std::endl;
}