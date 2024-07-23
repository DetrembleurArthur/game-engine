#ifndef __GE_RENDERER_COMPONENT_HPP__
#define __GE_RENDERER_COMPONENT_HPP__
#include <ge/entity/components/component.hpp>
#include <ge/graphics/renderer.hpp>

namespace ge
{
    class RendererComponent : public Component
    {
    private:
        Renderer *renderer=nullptr;
    public:
        using Component::Component;
        void set_renderer(ge::Renderer *renderer);
        ge::Renderer *get_renderer();
    };
}

#endif
