#include "ge/entity/rect.hpp"

ge::Rect::Rect() : Rect(1, 1, false, false)
{
}

ge::Rect::Rect(float width, float height, bool tex, bool dynamic) : Drawable() 
{
    init_rect_mesh(width, height, tex, dynamic);
}

ge::Rect::Rect(ge::Texture *texture, bool dynamic) : Drawable()
{
    if(texture)
    {
        set_texture(texture);
        glm::uvec2 tex_size = texture->get_size();
        init_rect_mesh(tex_size.x, tex_size.y, true, dynamic);
    }
}

void ge::Rect::init_rect_mesh(float width, float height, bool tex, bool dynamic)
{
    if(width > 0 && height > 0)
    {
        if(mesh)
        {
            dynamic = mesh->is_dynamic();
            delete mesh;
            mesh = nullptr;
        }
        transform.set_size(width, height);
        mesh = Mesh::create_rect(tex, dynamic);
    }
}

void ge::Rect::set_texture(const ge::Texture *texture)
{
    if(!this->texture)
    {
        ge::Drawable::set_texture(texture);
        init_rect_mesh(transform.get_width(), transform.get_height(), true);
        return;
    }
    else if(this->texture && !texture)
    {
        init_rect_mesh(transform.get_width(), transform.get_height(), false);
    }
    ge::Drawable::set_texture(texture);
}

void ge::Rect::update_uvs(glm::vec2 uvs_origin, glm::vec2 size)
{
    glBindBuffer(GL_ARRAY_BUFFER, mesh->get_vbo());
    float uvs[2] = {uvs_origin.x, uvs_origin.y};
    glBufferSubData(GL_ARRAY_BUFFER, (0 * 5 + 3) * sizeof(float), sizeof(float) * 2, (const void *)uvs);
    uvs[1] = uvs_origin.y + size.y;
    glBufferSubData(GL_ARRAY_BUFFER, (1 * 5 + 3) * sizeof(float), sizeof(float) * 2, (const void *)uvs);
    uvs[0] = uvs_origin.x + size.x;
    glBufferSubData(GL_ARRAY_BUFFER, (2 * 5 + 3) * sizeof(float), sizeof(float) * 2, (const void *)uvs);
    uvs[1] = uvs_origin.y;
    glBufferSubData(GL_ARRAY_BUFFER, (3 * 5 + 3) * sizeof(float), sizeof(float) * 2, (const void *)uvs);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
}
