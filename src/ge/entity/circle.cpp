#include "ge/entity/circle.hpp"

ge::Circle::Circle(int points, float radius) : Circle()
{
    this->points = points;
    init_circle_mesh(radius);
}

ge::Circle::Circle(int points, ge::Texture *texture) : Circle()
{
    if(texture)
    {
        this->texture = texture;
        glm::uvec2&& tex_size = texture->get_size();
        this->points = points;
        init_circle_mesh((tex_size.x + tex_size.y) / 4);
    }
}

void ge::Circle::init_circle_mesh(float radius)
{
    if(radius > 0)
    {
        if(mesh)
        {
            delete mesh;
            mesh = nullptr;
        }
        transform.set_size(radius * 2, radius * 2);
        mesh = Mesh::create_circle(points, texture != nullptr);
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
