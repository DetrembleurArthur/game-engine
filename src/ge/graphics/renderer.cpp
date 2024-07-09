#include "ge/graphics/renderer.hpp"

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

void ge::Renderer::draw(float dt, GameObject& go)
{
    shader->set_uniform_color(go.get_color());
    shader->set_uniform_model(go.get_transform().get_model());
    Mesh *mesh = go.get_mesh();
    if(camera)
    {
        camera->update_projection();
        camera->update_view();
        shader->set_uniform_view(camera->get_view());
        shader->set_uniform_projection(camera->get_projection());
        if(mesh)
        {
            const Texture *texture = go.get_texture();
            shader->set_uniform_enable_texture(texture && mesh->is_textured());
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
