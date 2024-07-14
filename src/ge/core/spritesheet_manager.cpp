#include "ge/core/spritesheet_manager.hpp"
#include <ge/utils/log.hpp>
#include <ge/utils/utils.hpp>

ge::SpritesheetManager::SpritesheetManager()
{
}

ge::SpritesheetManager::~SpritesheetManager()
{
    for(auto it = spritesheets.begin(); it != spritesheets.end(); it++)
    {
        if(it->second)
        {
            delete it->second;
            it->second = nullptr;
            log(it->first + " spritesheet deleted", LogLevels::SPRITESHEET);
        }
    }
}

void ge::SpritesheetManager::load(const ge::Texture *texture, int rows, int cols, int paddx, int paddy, bool last_padded, const std::string &name)
{
    ge::SpriteSheet *spritesheet = new ge::SpriteSheet(texture, rows, cols, paddx, paddy, last_padded);
    spritesheets[name] = spritesheet;
    log("load '" + name + "' as a spritesheet", LogLevels::SPRITESHEET);
}

void ge::SpritesheetManager::unload(const std::string &name)
{
    if(!name.empty())
    {
        log("unload " + name, LogLevels::SPRITESHEET);
        SpriteSheet *spritesheet = spritesheets[name];
        if(spritesheet)
        {
            delete spritesheet;
        }
        spritesheets.erase(name);
    }
}

ge::SpriteSheet *ge::SpritesheetManager::get(const std::string &name)
{
    return spritesheets[name];
}
