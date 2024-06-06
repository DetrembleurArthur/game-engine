#include "scene.hpp"
#include <log.hpp>
#include <shader.hpp>
#include <application.hpp>

ge::Scene::Scene(const std::string& name) : name(name), camera(new Camera2D()), renderer(new Renderer(ge::Shader::DEFAULT, camera))
{
    bg_mesh = Mesh::create_rect();
    bg_mesh->set_color(glm::vec4(1, 1, 1, 1));
    bg_transform = new Transform();
    bg_transform->set_size(Application::get().get_window().get_size().x, Application::get().get_window().get_size().y);
}

ge::Scene::~Scene()
{
    set_renderer(nullptr);
    if(camera)
        delete camera;
    if(bg_mesh)
        delete bg_mesh;
    if(bg_transform)
        delete bg_transform;
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
