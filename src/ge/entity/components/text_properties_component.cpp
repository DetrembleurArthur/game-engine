#include "ge/entity/components/text_properties_component.hpp"
#include "ge/entity/text.hpp"

ge::TextPropertiesComponent::TextPropertiesComponent(ge::GameObject *owner) : Component(owner)
{
    Text *text = dynamic_cast<Text *>(owner);
    if(text)
    {
        Color *shadow_color = &text->get_shadow_color();
        shadow_color_red_property.on_change([shadow_color](float red) {
            shadow_color->r = red;
        });
        shadow_color_green_property.on_change([shadow_color](float green) {
            shadow_color->g = green;
        });
        shadow_color_blue_property.on_change([shadow_color](float blue) {
            shadow_color->b = blue;
        });
        shadow_color_alpha_property.on_change([shadow_color](float alpha) {
            shadow_color->a = alpha;
        });
        shadow_color_property.on_change([shadow_color](Color new_color) {
            *shadow_color = new_color;
        });
        shadow_color_property.link<float>(&shadow_color_red_property,
            [](const Color& position) {
                return position.r;
            },
            [shadow_color](const float& red) {
                return Color(red, shadow_color->g, shadow_color->b, shadow_color->a);
        });
        shadow_color_property.link<float>(&shadow_color_green_property,
            [](const Color& position) {
                return position.g;
            },
            [shadow_color](const float& green) {
                return Color(shadow_color->r, green, shadow_color->b, shadow_color->a);
        });
        shadow_color_property.link<float>(&shadow_color_blue_property,
            [](const Color& position) {
                return position.b;
            },
            [shadow_color](const float& blue) {
                return Color(shadow_color->r, shadow_color->g, blue, shadow_color->a);
        });
        shadow_color_property.link<float>(&shadow_color_blue_property,
            [](const Color& position) {
                return position.a;
            },
            [shadow_color](const float& alpha) {
                return Color(shadow_color->r, shadow_color->g, shadow_color->b, alpha);
        });

        text_property.on_change([text](std::string str) {
            text->set_text(str);
        });
        shadow_x_property.on_change([text](float x) {
            text->set_shadow_offset(glm::vec2(x, text->get_shadow_offset().y));
        });
        shadow_y_property.on_change([text](float y) {
            text->set_shadow_offset(glm::vec2(text->get_shadow_offset().x, y));
        });
        shadow_offset_property.on_change([text](glm::vec2 offset) {
            text->set_shadow_offset(offset);
        });
        shadow_offset_property.link<float>(&shadow_x_property,
            [](const glm::vec2& offset) {
                return offset.x;
            }, [text](const float& x) {
                return glm::vec2(x, text->get_shadow_offset().y);
        });
        shadow_offset_property.link<float>(&shadow_y_property,
            [](const glm::vec2& offset) {
                return offset.y;
            }, [text](const float& y) {
                return glm::vec2(text->get_shadow_offset().y, y);
        });
        shadow_property.on_change([text](bool value) {
            text->enable_shadow(value);
        });

        text_width_property.on_change([text](float width) {
            text->set_text_width(width);
        });
        text_height_property.on_change([text](float height) {
            text->set_text_height(height);
        });
    }
}

ge::StrNotifyProperty& ge::TextPropertiesComponent::text()
{
    return text_property;
}

ge::StrNotifyProperty *ge::TextPropertiesComponent::p_text()
{
    return &text_property;
}

ge::BoolNotifyProperty& ge::TextPropertiesComponent::shadow()
{
    return shadow_property;
}

ge::BoolNotifyProperty* ge::TextPropertiesComponent::p_shadow() 
{
    return &shadow_property;
}

ge::FloatNotifyProperty& ge::TextPropertiesComponent::shadow_x()
{
    return shadow_x_property;  
}

ge::FloatNotifyProperty* ge::TextPropertiesComponent::p_shadow_x()
{
    return &shadow_x_property;
}

ge::FloatNotifyProperty& ge::TextPropertiesComponent::shadow_y() 
{
    return shadow_y_property;
}

ge::FloatNotifyProperty* ge::TextPropertiesComponent::p_shadow_y()
{
    return &shadow_y_property;
}

ge::Vec2NotifyProperty& ge::TextPropertiesComponent::shadow_offset() 
{
    return shadow_offset_property;
}

ge::Vec2NotifyProperty* ge::TextPropertiesComponent::p_shadow_offset() 
{
    return &shadow_offset_property;
}

ge::FloatNotifyProperty& ge::TextPropertiesComponent::shadow_color_red() 
{
    return shadow_color_red_property;
}

ge::FloatNotifyProperty* ge::TextPropertiesComponent::p_shadow_color_red() 
{
    return &shadow_color_red_property;
}

ge::FloatNotifyProperty& ge::TextPropertiesComponent::shadow_color_green() 
{
    return shadow_color_green_property;
}

ge::FloatNotifyProperty* ge::TextPropertiesComponent::p_shadow_color_green() 
{
    return &shadow_color_green_property;
}

ge::FloatNotifyProperty& ge::TextPropertiesComponent::shadow_color_blue() 
{
    return shadow_color_blue_property;
}

ge::FloatNotifyProperty* ge::TextPropertiesComponent::p_shadow_color_blue() 
{
    return &shadow_color_blue_property;
}

ge::FloatNotifyProperty& ge::TextPropertiesComponent::shadow_color_alpha() 
{
    return shadow_color_alpha_property;
}

ge::FloatNotifyProperty* ge::TextPropertiesComponent::p_shadow_color_alpha() 
{
    return &shadow_color_alpha_property;
}

ge::ColorNotifyProperty& ge::TextPropertiesComponent::shadow_color() 
{
    return shadow_color_property;
}

ge::ColorNotifyProperty* ge::TextPropertiesComponent::p_shadow_color() 
{
    return &shadow_color_property;
}

ge::FloatNotifyProperty& ge::TextPropertiesComponent::text_width() 
{
    return text_width_property;
}

ge::FloatNotifyProperty* ge::TextPropertiesComponent::p_text_width() 
{
    return &text_width_property;
}

ge::FloatNotifyProperty& ge::TextPropertiesComponent::text_height() 
{
    return text_height_property;
}

ge::FloatNotifyProperty* ge::TextPropertiesComponent::p_text_height()
{
    return &text_height_property;
}
