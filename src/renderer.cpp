#include "renderer.hpp"

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

void ge::Renderer::draw(float dt, VertexBuffer &vb, Transform& tr)
{
    shader->set_uniform_color(vb.get_color());
    shader->set_uniform_model(tr.get_model());
    if(camera)
    {
        camera->update_projection();
        camera->update_view();
        shader->set_uniform_view(camera->get_view());
        shader->set_uniform_projection(camera->get_projection());
    }
    vb.draw();
}

void ge::Renderer::set_camera(Camera2D *camera)
{
    this->camera = camera;
}
