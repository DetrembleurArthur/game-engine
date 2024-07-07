#include "scene.hpp"
#include <log.hpp>
#include <shader.hpp>
#include <algorithm>
#include <application.hpp>


ge::Scene::Scene(const std::string& name, int layers_number) : app(ge::Application::get()), name(name), camera(new Camera2D()), renderer(new Renderer(ge::Shader::DEFAULT, camera)), textures(new TextureManager())
{
    for(int i = 0; i < layers_number; i++)
    {
        layers.push_back(Layer());
    }
}

ge::Scene::~Scene()
{
    for(Layer& layer : layers)
    {
        for(std::pair<GameObject *, GoInfos>& go : layer.first)
        {
            if(go.second.freeable)
            {
                if(go.first)
                {
                    delete go.first;
                    go.first = nullptr;
                }
            }
        }
        layer.first.clear();
    }
    layers.clear();
    set_renderer(nullptr);
    if(camera)
        delete camera;
    if(textures)
        delete textures;
}

void ge::Scene::update(double dt)
{
    for(Layer& layer : layers)
    {
        if(layer.second.kill_enabled)
        {
            layer.first.erase(std::remove_if(layer.first.begin(), layer.first.end(), [](std::pair<GameObject *, GoInfos>& go) {
                bool to_kill = go.first->get_flags().killed;
                if(to_kill && go.second.freeable)
                    delete go.first;
                return to_kill;
            }));
            layer.second.kill_enabled = false;
        }
        for(std::pair<GameObject *, GoInfos>& go : layer.first)
        {
            go.first->update(dt);
        }
    }
}

void ge::Scene::draw(double dt)
{
    renderer->begin();
    for(Layer& layer : layers)
    {
        for(std::pair<GameObject *, GoInfos>& go : layer.first)
        {
            GameObject *ptr = go.first;
            if(ptr->drawable())
                renderer->draw(dt, *ptr);
        }
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

void ge::Scene::kill(GameObject &go, int layer_id)
{
    layers[layer_id].second.kill_enabled = go.get_flags().killed = true;
}

void ge::Scene::kill(GameObject *go, int layer_id)
{
    if(go)
        kill(*go);
    else
        layers[layer_id].second.kill_enabled = true;
}

std::string ge::Scene::get_name()
{
    return name;
}

ge::Camera2D *ge::Scene::get_camera()
{
    return camera;
}

void ge::Scene::add(GameObject& go, int layer_id, GoInfos infos)
{
    if(layers.size() > layer_id)
        layers[layer_id].first.push_back(std::pair<GameObject *, GoInfos>(&go, infos));
}

void ge::Scene::add(GameObject *go, int layer_id, GoInfos infos)
{
    if(go)
        add(*go, layer_id, infos);
}
