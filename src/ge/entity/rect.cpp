#include "ge/entity/rect.hpp"


ge::Rect::Rect(float width, float height) : Rect() 
{
    init_rect_mesh(width, height);
}

ge::Rect::Rect(ge::Texture *texture) : Rect()
{
    if(texture)
    {
        set_texture(texture);
        glm::uvec2 tex_size = texture->get_size();
        init_rect_mesh(tex_size.x, tex_size.y);
    }
}

void ge::Rect::init_rect_mesh(float width, float height)
{
    if(width > 0 && height > 0)
    {
        if(mesh)
        {
            delete mesh;
            mesh = nullptr;
        }
        transform.set_size(width, height);
        mesh = Mesh::create_rect(texture != nullptr);
    }
}
