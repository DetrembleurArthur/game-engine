#include "ge/core/renderer_manager.hpp"

ge::RendererManager::RendererManager(Renderer *default_renderer) : default_renderer(default_renderer)
{
    set("default", default_renderer);
}

ge::RendererManager::~RendererManager()
{
    for(auto it = renderers.begin(); it != renderers.end(); it++)
    {
        if(it->second)
        {
            delete it->second;
            log("destroy " + it->first, ge::LogLevels::RENDERER);
        }
    }
    renderers.clear();
}

void ge::RendererManager::set_default(const std::string &name)
{
    default_renderer = get(name);
}

ge::Renderer *ge::RendererManager::get_default()
{
    return default_renderer;
}

void ge::RendererManager::set(const std::string &name, ge::Renderer *renderer)
{
    if(renderer)
    {
        if(renderers.find(name) == renderers.end())
        {
            renderers[name] = renderer;
            log("register " + name, LogLevels::RENDERER);
        }
    }
}

ge::Renderer *ge::RendererManager::get(const std::string &name)
{
    if(renderers.find(name) != renderers.end())
        return renderers[name];
    return nullptr;
}
