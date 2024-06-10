#include "scene.hpp"
#include <log.hpp>
#include <shader.hpp>
#include <application.hpp>

ge::Scene::Scene(const std::string& name) : name(name), camera(new Camera2D()), renderer(new Renderer(ge::Shader::DEFAULT, camera)), textures(new TextureManager())
{
    
}

ge::Scene::~Scene()
{
    set_renderer(nullptr);
    if(camera)
        delete camera;
    if(textures)
        delete textures;
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

ge::Camera2D *ge::Scene::get_camera()
{
    return camera;
}
