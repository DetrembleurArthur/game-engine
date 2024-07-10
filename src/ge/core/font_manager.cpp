#include "ge/core/font_manager.hpp"
#include <fstream>

ge::FontManager::~FontManager()
{
    for(auto it = fonts.begin(); it != fonts.end(); it++)
    {
        if(it->second)
        {
            delete it->second;
            it->second = nullptr;
            log(it->first + " deleted", LogLevels::FONT);
        }
    }
}

void ge::FontManager::load(const std::string &filename, const std::string &name, int font_size)
{
    if(!filename.empty() && !name.empty())
    {
        if(fonts.find(name) == fonts.end())
        {
            ge::Font *font = new ge::Font(filename, font_size);
            fonts[name] = font;
            log("font '" + name + "' => '" + filename + "' registered in the FontManager", LogLevels::FONT);
        }
        else
        {
            log("font '" + name + "' already exists", LogLevels::WARNING);
        }
    }
    else
    {
        log("can not register font '" + name + "' => '" + filename + "", LogLevels::ERROR);
    }
}

void ge::FontManager::unload(const std::string& name)
{
    if(!name.empty() && fonts.find(name) != fonts.end())
    {
        ge::Font *font = fonts[name];
        if(font)
        {
            delete fonts[name];
        }
        fonts.erase(name);
    }
}

ge::Font *ge::FontManager::get(const std::string& name)
{
    return fonts[name];
}
