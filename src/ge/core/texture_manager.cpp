#include "ge/core/texture_manager.hpp"
#include <ge/utils/log.hpp>
#include <ge/utils/utils.hpp>

ge::TextureManager::TextureManager()
{
}

ge::TextureManager::~TextureManager()
{
    for(auto it = textures.begin(); it != textures.end(); it++)
    {
        if(it->second)
        {
            delete it->second;
            it->second = nullptr;
            log(it->first + " deleted", LogLevels::TEXTURE);
        }
    }
}

void ge::TextureManager::load(const std::string &filename, const std::string &name)
{
    auto file_infos = ge::utils::name_and_ext(filename);
    if(!file_infos.first.empty())
    {
        Texture *texture = Texture::load(filename, file_infos.second != "png");
        textures[name.empty() ? file_infos.first : name] = texture;
        log("load '" + filename + "' as " + (name.empty() ? file_infos.first : name), LogLevels::TEXTURE);
    }
}

void ge::TextureManager::unload(const std::string &name)
{
    if(!name.empty())
    {
        log("unload " + name, LogLevels::TEXTURE);
        Texture *texture = textures[name];
        if(texture)
        {
            delete texture;
        }
        textures.erase(name);
    }
}

ge::Texture *ge::TextureManager::get(const std::string &name)
{
    return textures[name];
}
