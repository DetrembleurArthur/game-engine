#ifndef __GE_TEXT_PROPERTIES_COMPONENT_HPP__
#define __GE_TEXT_PROPERTIES_COMPONENT_HPP__
#include <ge/entity/components/component.hpp>
#include <ge/binding/notify_property.hpp>

namespace ge
{
    class TextPropertiesComponent : public Component
    {
    private:
        StrNotifyProperty text_property;
        BoolNotifyProperty shadow_property;
        FloatNotifyProperty shadow_x_property;
        FloatNotifyProperty shadow_y_property;
        Vec2NotifyProperty shadow_offset_property;
        FloatNotifyProperty shadow_color_red_property;
        FloatNotifyProperty shadow_color_green_property;
        FloatNotifyProperty shadow_color_blue_property;
        FloatNotifyProperty shadow_color_alpha_property;
        ColorNotifyProperty shadow_color_property;
        FloatNotifyProperty text_width_property;
        FloatNotifyProperty text_height_property;
    public:
        TextPropertiesComponent(GameObject *owner);
        StrNotifyProperty& text();
        StrNotifyProperty *p_text();
        BoolNotifyProperty& shadow();
        BoolNotifyProperty* p_shadow();
        FloatNotifyProperty& shadow_x();
        FloatNotifyProperty* p_shadow_x();
        FloatNotifyProperty& shadow_y();
        FloatNotifyProperty* p_shadow_y();
        Vec2NotifyProperty& shadow_offset();
        Vec2NotifyProperty* p_shadow_offset();
        FloatNotifyProperty& shadow_color_red();
        FloatNotifyProperty* p_shadow_color_red();
        FloatNotifyProperty& shadow_color_green();
        FloatNotifyProperty* p_shadow_color_green();
        FloatNotifyProperty& shadow_color_blue();
        FloatNotifyProperty* p_shadow_color_blue();
        FloatNotifyProperty& shadow_color_alpha();
        FloatNotifyProperty* p_shadow_color_alpha();
        ColorNotifyProperty& shadow_color();
        ColorNotifyProperty* p_shadow_color();
        FloatNotifyProperty& text_width();
        FloatNotifyProperty* p_text_width();
        FloatNotifyProperty& text_height();
        FloatNotifyProperty* p_text_height();
    };
}

#endif
