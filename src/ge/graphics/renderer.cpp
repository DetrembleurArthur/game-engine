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


void ge::Renderer::set_camera(Camera2D *camera)
{
    this->camera = camera;
}

void ge::BasicRenderer::draw(float dt, Drawable *go)
{
    Mesh *mesh = go->get_mesh();
    if(camera && mesh)
    {
        camera->update_projection();
        camera->update_view();
        shader->set_uniform_view(camera->get_view());
        shader->set_uniform_projection(camera->get_projection());
        shader->set_uniform_color(go->get_color());
        shader->set_uniform_model(go->get_transform().get_model());
        mesh->draw();
    }
}

void ge::TexRenderer::draw(float dt, Drawable *go)
{
    Mesh *mesh = go->get_mesh();
    const ge::Texture *texture = go->get_texture();
    if(camera && mesh && texture)
    {
        camera->update_projection();
        camera->update_view();
        shader->set_uniform_view(camera->get_view());
        shader->set_uniform_projection(camera->get_projection());
        shader->set_uniform_color(go->get_color());
        shader->set_uniform_model(go->get_transform().get_model());
        texture->active();
        texture->bind();
        shader->set_uniform_texture();
        mesh->draw();
    }
}

void ge::TextRenderer::draw(float dt, Drawable* go)
{
    ge::Text *text = dynamic_cast<ge::Text *>(go);
    Mesh *mesh = text->get_mesh();
    const Texture *texture = text->get_texture();
    if(text && camera && mesh && texture)
    {
        camera->update_projection();
        camera->update_view();
        shader->set_uniform_view(camera->get_view());
        shader->set_uniform_projection(camera->get_projection());
        if(text->is_shadow_enabled())
        {
            text->get_transform().set_position(text->get_transform().get_position() + text->get_shadow_offset());
            shader->set_uniform_color(text->get_shadow_color());
            shader->set_uniform_model(text->get_transform().get_model());
            texture->active();
            texture->bind();
            shader->set_uniform_texture();
            mesh->draw();
            text->get_transform().set_position(text->get_transform().get_position() - text->get_shadow_offset());
        }
        else
        {
            texture->active();
            texture->bind();
            shader->set_uniform_texture();
        }
        shader->set_uniform_color(text->get_color());
        shader->set_uniform_model(text->get_transform().get_model());
        mesh->draw();
    }
}
