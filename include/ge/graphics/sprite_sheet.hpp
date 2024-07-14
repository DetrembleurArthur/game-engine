#ifndef __GE_SPRITESHEET_HPP__
#define __GE_SPRITESHEET_HPP__
#include <ge/graphics/texture.hpp>
#include <map>
#include <vector>

namespace ge
{
    struct Sprite
    {
        glm::vec2 uvs;
    };

    class SpriteSheet
    {
    private:
        const ge::Texture *texture=nullptr;
        int rows=0;
        int cols=0;
        int paddx=0;
        int paddy=0;
        glm::vec2 sprite_size;
        glm::vec2 uvs_size;
        glm::vec2 uvs_padd_size;
        std::map<std::string, std::vector<Sprite>> sprite_sets;
    public:
        SpriteSheet(const ge::Texture *texture, int rows, int cols, int paddx=0, int paddy=0, bool last_padded=true);
        void define_sprite_set(const std::string& name, int begin_index, int end_index);
        void define_sprite_set(const std::string& name, int row);
        ge::Sprite get_sprite(int index);
        std::vector<ge::Sprite>& get_sprite_set(const std::string& name);
        const ge::Texture *get_texture();
        glm::vec2 get_uvs_size() const;
    };
}

#endif
