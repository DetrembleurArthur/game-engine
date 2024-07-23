#ifndef __GE_FONT_MANAGER_HPP__
#define __GE_FONT_MANAGER_HPP__
#include <ge/graphics/text/font.hpp>

namespace ge
{
    class FontManager
    {
    private:
        std::map<std::string, ge::Font *> fonts;
    public:
        ~FontManager();
        void load(const std::string& filename, const std::string& name, int font_size, const std::string& charset="");
        void unload(const std::string& name);
        ge::Font *get(const std::string& name);
    };
}

#endif

