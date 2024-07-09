#include "ge/entity/game_object.hpp"


ge::GameObject::GameObject() : color(1, 1, 1, 1), flags({false, false})
{

}

ge::GameObject::~GameObject()
{
    for(Component *c : components)
    {
        if(c)
            delete c;
    }
    components.clear();
    if(mesh)
    {
        delete mesh;
    }
}

void ge::GameObject::as_rect(float width, float height)
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

void ge::GameObject::as_rect(const Texture *texture)
{
    if(texture)
    {
        this->texture = texture;
        glm::uvec2 tex_size = texture->get_size();
        as_rect(tex_size.x, tex_size.y);
    }
}

void ge::GameObject::as_circle(int points, float radius)
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

void ge::GameObject::as_circle(int points, const Texture *texture)
{
    if(texture)
    {
        this->texture = texture;
        glm::uvec2&& tex_size = texture->get_size();
        as_circle(points, (tex_size.x + tex_size.y) / 4);
    }
}

void ge::GameObject::as_text()
{
    if(mesh)
    {
        delete mesh;
        mesh = nullptr;
    }
    mesh = Mesh::create_text();
}

void ge::GameObject::set_color(Color color)
{
    this->color = color;
}

ge::Color &ge::GameObject::get_color()
{
    return color;
}

ge::Mesh *ge::GameObject::get_mesh()
{
    return mesh;
}

const ge::Texture *ge::GameObject::get_texture()
{
    return texture;
}

ge::Transform &ge::GameObject::get_transform()
{
    return transform;
}

void ge::GameObject::update(float dt)
{
    if(!flags.disabled)
    {
        for(Component *c : components)
        {
            if(dynamic_cast<UpdatableComponent *>(c))
            {
                dynamic_cast<UpdatableComponent *>(c)->update(dt);
            }
        }
    }
}

bool ge::GameObject::drawable()
{
    return mesh;
}

ge::GOFlags &ge::GameObject::get_flags()
{
    return flags;
}

ge::GameObject::operator Transform &()
{
    return transform;
}
