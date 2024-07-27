#include "ge/core/scene.hpp"
#include <ge/utils/log.hpp>
#include <ge/graphics/shader.hpp>
#include <algorithm>
#include <ge/core/application.hpp>
#include <ge/entity/node.hpp>
#include <ge/inputs/mouse_input.hpp>
#include <ge/entity/components/renderer_component.hpp>


ge::Scene::Scene(const std::string& name, int layers_number) : app(ge::Application::get()),
    name(name),
    camera(new Camera2D()),
    ui_camera(new Camera2D()),
    renderers(new RendererManager(new ge::BasicRenderer(ge::Shader::BASIC, camera))),
    textures(new TextureManager()),
    fonts(new FontManager()),
    spritesheets(new SpritesheetManager()),
    sounds(new SoundManager())
{
    for(int i = 0; i < layers_number; i++)
    {
        layers.push_back(Layer());
    }
    renderers->set("ui", new ge::BasicRenderer(ge::Shader::BASIC, get_ui_camera()));
    renderers->set("tex", new ge::TexRenderer(ge::Shader::TEX, get_camera()));
    renderers->set("tex_ui", new ge::TexRenderer(ge::Shader::TEX, get_ui_camera()));
    renderers->set("text", new ge::TextRenderer(ge::Shader::TEXT, get_camera()));
    renderers->set("text_ui", new ge::TextRenderer(ge::Shader::TEXT, get_ui_camera()));
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
    if(camera)
        delete camera;
    if(ui_camera)
        delete ui_camera;
    if(renderers)
        delete renderers;
    if(textures)
        delete textures;
    if(fonts)
        delete fonts;
    if(spritesheets)
        delete spritesheets;
    if(sounds)
        delete sounds;
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
    Renderer *renderer = nullptr;
    for(Layer& layer : layers)
    {
        for(std::pair<GameObject *, GoInfos>& go : layer.first)
        {
            Drawable *ptr = dynamic_cast<Drawable *>(go.first);
            if(ptr)
            {
                if(ptr->has_component<ge::RendererComponent>())
                {
                    renderer = ptr->get_component<ge::RendererComponent>().get_renderer();
                }
                else
                {
                    renderer = renderers->get_default();
                }
                renderer->begin();
                renderer->draw(dt, ptr);
                renderer->end();
            }
            else if(dynamic_cast<Node *>(go.first))
            {
                for(Drawable *dr : dynamic_cast<Node *>(go.first)->get_drawable_cache())
                {
                    if(dr->has_component<ge::RendererComponent>())
                    {
                        renderer = dr->get_component<ge::RendererComponent>().get_renderer();
                    }
                    else
                    {
                        renderer = renderers->get_default();
                    }
                    renderer->begin();
                    renderer->draw(dt, dr);
                    renderer->end();
                }
            }
        }
    }
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

ge::Camera2D *ge::Scene::get_ui_camera()
{
    return ui_camera;
}

glm::vec2 ge::Scene::get_mp()
{
    return ge::MouseInput::get_position(camera);
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
