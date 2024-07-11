#include "ge/graphics/renderer.hpp"
#include <ge/entity/text.hpp>

ge::Renderer::Renderer(Shader *shader, Camera2D *camera) : shader(shader), camera(camera)
{
}

void ge::Renderer::begin()
{
    shader->use();
}

void ge::Renderer::end()
{
    shader->unuse();
}

void ge::Renderer::draw_text(float dt, ge::Text *go)
{
    Mesh *mesh = go->get_mesh();
    const Texture *texture = go->get_texture();
    shader->set_uniform_enable_texture(2);
    if(go->is_shadow_enabled())
    {
        go->get_transform().set_position(go->get_transform().get_position() + go->get_shadow_offset());
        shader->set_uniform_color(go->get_shadow_color());
        shader->set_uniform_model(go->get_transform().get_model());
        texture->active();
        texture->bind();
        shader->set_uniform_texture();
        mesh->draw();
        go->get_transform().set_position(go->get_transform().get_position() - go->get_shadow_offset());
    }
    else
    {
        texture->active();
        texture->bind();
        shader->set_uniform_texture();
    }

    shader->set_uniform_color(go->get_color());
    shader->set_uniform_model(go->get_transform().get_model());
    mesh->draw();
}

void ge::Renderer::draw(float dt, Drawable* go)
{
    Mesh *mesh = go->get_mesh();
    if(camera)
    {
        camera->update_projection();
        camera->update_view();
        shader->set_uniform_view(camera->get_view());
        shader->set_uniform_projection(camera->get_projection());
        if(mesh)
        {
            const Texture *texture = go->get_texture();
            if(dynamic_cast<Text *>(go))
            {
                draw_text(dt, dynamic_cast<Text *>(go));
                return;
            }
            else
            {
                shader->set_uniform_color(go->get_color());
                shader->set_uniform_model(go->get_transform().get_model());
                shader->set_uniform_enable_texture(texture && mesh->is_textured());
            }
            if(texture)
            {
                texture->active();
                texture->bind();
                shader->set_uniform_texture();
            }

        }
    }
    if(mesh)
        mesh->draw();
}

void ge::Renderer::set_camera(Camera2D *camera)
{
    this->camera = camera;
}
