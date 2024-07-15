#include "ge/entity/components/color_properties_component.hpp"
#include "ge/entity/drawable.hpp"

ge::ColorPropertiesComponent::ColorPropertiesComponent(ge::GameObject *owner) : Component(owner)
{
    Drawable *dr = dynamic_cast<Drawable *>(owner);
    Color* color = &dr->get_color();
    if(dr)
    {
        red_property.on_change([color](float red) {
            color->r = red;
        });
        green_property.on_change([color](float green) {
            color->g = green;
        });
        blue_property.on_change([color](float blue) {
            color->b = blue;
        });
        alpha_property.on_change([color](float alpha) {
            color->a = alpha;
        });
        color_property.on_change([color](Color new_color) {
            *color = new_color;
        });
        color_property.link<float>(&red_property,
            [](const Color& position) {
                return position.r;
            },
            [color](const float& red) {
                return Color(red, color->g, color->b, color->a);
        });
        color_property.link<float>(&green_property,
            [](const Color& position) {
                return position.g;
            },
            [color](const float& green) {
                return Color(color->r, green, color->b, color->a);
        });
        color_property.link<float>(&blue_property,
            [](const Color& position) {
                return position.b;
            },
            [color](const float& blue) {
                return Color(color->r, color->g, blue, color->a);
        });
        color_property.link<float>(&alpha_property,
            [](const Color& position) {
                return position.a;
            },
            [color](const float& alpha) {
                return Color(color->r, color->g, color->b, alpha);
        });
    }   
}

ge::FloatNotifyProperty &ge::ColorPropertiesComponent::red()
{
    return red_property;
}

ge::FloatNotifyProperty *ge::ColorPropertiesComponent::p_red()
{
    return &red_property;
}

ge::FloatNotifyProperty &ge::ColorPropertiesComponent::green()
{
    return green_property;
}

ge::FloatNotifyProperty *ge::ColorPropertiesComponent::p_green()
{
    return &green_property;
}

ge::FloatNotifyProperty &ge::ColorPropertiesComponent::blue()
{
    return blue_property;
}

ge::FloatNotifyProperty *ge::ColorPropertiesComponent::p_blue()
{
    return &blue_property;
}

ge::FloatNotifyProperty &ge::ColorPropertiesComponent::alpha()
{
    return alpha_property;
}

ge::FloatNotifyProperty *ge::ColorPropertiesComponent::p_alpha()
{
    return &alpha_property;
}

ge::ColorNotifyProperty &ge::ColorPropertiesComponent::color()
{
    return color_property;
}

ge::ColorNotifyProperty *ge::ColorPropertiesComponent::p_color()
{
    return &color_property;
}
