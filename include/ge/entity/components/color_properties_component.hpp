#ifndef __GE_COLOR_PROPERTIES_COMPONENT_HPP__
#define __GE_COLOR_PROPERTIES_COMPONENT_HPP__
#include <ge/entity/components/component.hpp>
#include <ge/binding/notify_property.hpp>

namespace ge
{
    class ColorPropertiesComponent : public Component
    {
    private:
        FloatNotifyProperty red_property;
        FloatNotifyProperty green_property;
        FloatNotifyProperty blue_property;
        FloatNotifyProperty alpha_property;
        ColorNotifyProperty color_property;
    public:
        ColorPropertiesComponent(GameObject *owner);
        FloatNotifyProperty& red();
        FloatNotifyProperty *p_red();
        FloatNotifyProperty& green();
        FloatNotifyProperty *p_green();
        FloatNotifyProperty& blue();
        FloatNotifyProperty *p_blue();
        FloatNotifyProperty& alpha();
        FloatNotifyProperty *p_alpha();
        ColorNotifyProperty& color();
        ColorNotifyProperty *p_color();
    };
}

#endif
