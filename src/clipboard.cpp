#include "clipboard.hpp"
#include <GLFW/glfw3.h>
#include <log.hpp>


std::string ge::Clipboard::get()
{
    std::string text = glfwGetClipboardString(nullptr);
    log("get \"" + text + "\"", LogLevels::CLIPBOARD);
    return text;
}

void ge::Clipboard::set(const std::string &text)
{
    glfwSetClipboardString(nullptr, text.c_str());
    log("set \"" + text + "\"", LogLevels::CLIPBOARD);
}
