#ifndef __GE_SPRITESHEET_MANAGER_HPP__
#define __GE_SPRITESHEET_MANAGER_HPP__
#include <map>
#include <ge/graphics/sprite_sheet.hpp>

namespace ge
{
    class SpritesheetManager
    {
    private:
        std::map<std::string, ge::SpriteSheet *> spritesheets;
    public:
        SpritesheetManager();
        ~SpritesheetManager();
        void load(const ge::Texture *texture, int rows, int cols, int paddx=0, int paddy=0, bool last_padded=true, const std::string& name="");
        void unload(const std::string& name);
        ge::SpriteSheet *get(const std::string& name);
    };
}


#endif

