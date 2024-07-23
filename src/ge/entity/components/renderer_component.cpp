#include "ge/entity/components/renderer_component.hpp"

void ge::RendererComponent::set_renderer(ge::Renderer *renderer)
{
    this->renderer = renderer;
}

ge::Renderer *ge::RendererComponent::get_renderer()
{
    return renderer;
}
