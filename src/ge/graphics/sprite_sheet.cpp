#include "ge/graphics/sprite_sheet.hpp"

ge::SpriteSheet::SpriteSheet(const ge::Texture *texture, int rows, int cols, int paddx, int paddy, bool last_padded) : texture(texture), rows(rows), cols(cols), paddx(paddx), paddy(paddy)
{
    glm::uvec2&& tex_size = texture->get_size();
    sprite_size.x = (tex_size.x - paddx * ((float)cols - !last_padded)) / (float)cols;
    sprite_size.y = (tex_size.y - paddy * ((float)rows - !last_padded)) / (float)rows;
    uvs_size.x = sprite_size.x / tex_size.x;
    uvs_size.y = sprite_size.y / tex_size.y;
    uvs_padd_size.x = (float)paddx / tex_size.x;
    uvs_padd_size.y = (float)paddy / tex_size.y;
}

void ge::SpriteSheet::define_sprite_set(const std::string &name, int begin_index, int end_index)
{
    if(begin_index < end_index)
    {
        std::vector<Sprite> sprites;
        while(begin_index <= end_index)
        {
            Sprite sprite = get_sprite(begin_index);
            sprites.push_back(sprite);
            begin_index++;
        }
        sprite_sets[name] = sprites;
    }
}

void ge::SpriteSheet::define_sprite_set(const std::string &name, int row)
{
    if(row >= 0)
    {
        define_sprite_set(name, row * cols, row * cols + cols - 1);
    }
}

ge::Sprite ge::SpriteSheet::get_sprite(int index)
{
    int row = index / cols;
    int col = index % rows;
    glm::vec2 coords(
        coords.x = col * uvs_size.x + uvs_padd_size.x * col,
        coords.y = row * uvs_size.y + uvs_padd_size.y * row);
    Sprite sprite;
    sprite.uvs = coords;
    return sprite;
}

std::vector<ge::Sprite> &ge::SpriteSheet::get_sprite_set(const std::string &name)
{
    return sprite_sets[name];
}

const ge::Texture *ge::SpriteSheet::get_texture()
{
    return texture;
}

glm::vec2 ge::SpriteSheet::get_uvs_size() const
{
    return uvs_size;
}
