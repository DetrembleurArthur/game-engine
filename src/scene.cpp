#include "scene.hpp"
#include <log.hpp>
#include <shader.hpp>
#include <application.hpp>

ge::Scene::Scene(const std::string& name) : name(name), camera(new Camera2D()), renderer(new Renderer(ge::Shader::DEFAULT, camera)), textures(new TextureManager())
{
    
}

ge::Scene::~Scene()
{
    for(std::pair<GameObject *, GoInfos>& go : game_objects)
    {
        if(go.second.removable)
        {
            if(go.first)
            {
                delete go.first;
                go.first = nullptr;
            }
        }
    }
    game_objects.clear();
    set_renderer(nullptr);
    if(camera)
        delete camera;
    if(textures)
        delete textures;
}

void ge::Scene::update(double dt)
{
    for(std::pair<GameObject *, GoInfos>& go : game_objects)
    {
        go.first->update(dt);
    }
}

void ge::Scene::draw(double dt)
{
    renderer->begin();
    for(std::pair<GameObject *, GoInfos>& go : game_objects)
    {
        GameObject *ptr = go.first;
        if(ptr->drawable())
            renderer->draw(dt, *ptr);
    }
    renderer->end();
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

void ge::Scene::add(GameObject& go, GoInfos infos)
{
    game_objects.push_back(std::pair<GameObject *, GoInfos>(&go, infos));
}

void ge::Scene::add(GameObject *go, GoInfos infos)
{
    if(go)
        add(*go, infos);
}
