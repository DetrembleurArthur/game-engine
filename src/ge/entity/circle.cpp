#include "ge/entity/circle.hpp"

ge::Circle::Circle(int points, float radius, bool tex, bool dynamic) : Circle()
{
    this->points = points;
    init_circle_mesh(radius, tex, dynamic);
}

ge::Circle::Circle(int points, const ge::Texture *texture, bool dynamic) : Circle()
{
    if(texture)
    {
        this->texture = texture;
        glm::uvec2&& tex_size = texture->get_size();
        this->points = points;
        init_circle_mesh((tex_size.x + tex_size.y) / 4, true, dynamic);
    }
}

void ge::Circle::init_circle_mesh(float radius, bool tex, bool dynamic)
{
    if(radius > 0)
    {
        if(mesh)
        {
            dynamic = mesh->is_dynamic();
            delete mesh;
            mesh = nullptr;
        }
        transform.set_size(radius * 2, radius * 2);
        mesh = Mesh::create_circle(points, tex, dynamic);
    }
}

void ge::Circle::set_points(int points)
{
    this->points = points;
    init_circle_mesh(get_radius());
}

void ge::Circle::set_radius(float radius)
{
    transform.set_size(radius * 2, radius * 2);
}

int ge::Circle::get_points() const
{
    return points;
}

float ge::Circle::get_radius()
{
    auto&& size = transform.get_size();
    return (size.x + size.y) / 4.0;
}

void ge::Circle::update_uvs(glm::vec2 uvs_origin, glm::vec2 size)
{
    glBindBuffer(GL_ARRAY_BUFFER, mesh->get_vbo());
    float angle = glm::radians(360.0 / points);
    float uvs[2] = {uvs_origin.x+size.x/2, uvs_origin.y+size.y/2};
    glBufferSubData(GL_ARRAY_BUFFER, (0 * 5 + 3) * sizeof(float), sizeof(float) * 2, (const void *)uvs);
    for(int i = 1; i <= points; i++)
    {
        uvs[0] = uvs_origin.x+size.x/2 + ((size.x/2) * std::sin(angle * (i-1)));
        uvs[1] = uvs_origin.y+size.y/2 + (-(size.y/2) * std::cos(angle * (i-1)));
        glBufferSubData(GL_ARRAY_BUFFER, (i * 5 + 3) * sizeof(float), sizeof(float) * 2, (const void *)uvs);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ge::Circle::set_texture(const ge::Texture *texture)
{
    if(!this->texture)
    {
        ge::Drawable::set_texture(texture);
        init_circle_mesh(get_radius(), true);
        return;
    }
    else if(this->texture && !texture)
    {
        init_circle_mesh(get_radius(), false);
    }
    ge::Drawable::set_texture(texture);
}
