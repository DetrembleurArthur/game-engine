#ifndef __GE_CLIPBOARD_HPP__
#define __GE_CLIPBOARD_HPP__
#include <string>

namespace ge
{
    class Clipboard
    {
    public:
        static std::string get();
        static void set(const std::string& text);
    };
}

#endif

