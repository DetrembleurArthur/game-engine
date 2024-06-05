#include "scene.hpp"
#include <log.hpp>
#include <shader.hpp>

ge::Scene::Scene(const std::string& name) : name(name), renderer(new Renderer(ge::Shader::DEFAULT))
{
}

ge::Scene::~Scene()
{
    set_renderer(nullptr);
}

void ge::Scene::set_renderer(ge::Renderer *renderer)
{
    if(this->renderer)
    {
        delete this->renderer;
        this->renderer = nullptr;
    }
    this->renderer = renderer;
}

std::string ge::Scene::get_name()
{
    return name;
}
