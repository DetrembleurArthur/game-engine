#include "ge/entity/drawable.hpp"

ge::Drawable::Drawable() : ge::GameObject(), color(1, 1, 1, 1)
{
}

ge::Drawable::~Drawable()
{
    if(mesh)
    {
        delete mesh;
        mesh = nullptr;
    }
}

void ge::Drawable::set_color(ge::Color color)
{
    this->color = color;
}

ge::Color& ge::Drawable::get_color()
{
    return color;
}

ge::Mesh *ge::Drawable::get_mesh()
{
    return mesh;
}

const ge::Texture *ge::Drawable::get_texture()
{
    return texture;
}

void ge::Drawable::set_texture(const ge::Texture *texture)
{
    this->texture = texture;
}

void ge::Drawable::update_uvs(glm::vec2 uvs_origin, glm::vec2 size)
{
    log("unimplemented for this class...", LogLevels::WARNING);
}
