#include "renderer.hpp"

ge::Renderer::Renderer(Shader *shader) : shader(shader)
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

void ge::Renderer::draw(float dt, VertexBuffer &vb)
{
    shader->set_uniform_color(vb.get_color());
    vb.draw();
}
