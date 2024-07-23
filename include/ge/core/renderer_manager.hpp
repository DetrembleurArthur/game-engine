#ifndef __GE_RENDERER_MANAGER_HPP__
#define __GE_RENDERER_MANAGER_HPP__
#include <ge/graphics/renderer.hpp>
#include <map>
#include <string>

namespace ge
{
    class RendererManager
    {
    private:
        Renderer *default_renderer=nullptr;
        std::map<std::string, Renderer *> renderers;
    public:
        RendererManager(Renderer *default_renderer);
        virtual ~RendererManager();
        void set_default(const std::string& name);
        ge::Renderer *get_default();
        void set(const std::string& name, ge::Renderer *renderer);
        ge::Renderer *get(const std::string& name);
    };
}

#endif
