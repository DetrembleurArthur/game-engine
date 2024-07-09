#ifndef __GE_TEXTURE_MANAGER_HPP__
#define __GE_TEXTURE_MANAGER_HPP__
#include <map>
#include <ge/graphics/texture.hpp>

namespace ge
{
    class TextureManager
    {
    private:
        std::map<std::string, ge::Texture *> textures;
    public:
        TextureManager();
        ~TextureManager();
        void load(const std::string& filename, const std::string& name="");
        void unload(const std::string& name);
        ge::Texture *get(const std::string& name);
    };
}


#endif

