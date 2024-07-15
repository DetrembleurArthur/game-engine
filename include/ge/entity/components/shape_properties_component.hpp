#ifndef __GE_PROPERTIES_COMPONENT_HPP__
#define __GE_PROPERTIES_COMPONENT_HPP__
#include <ge/entity/components/component.hpp>
#include <ge/binding/notify_property.hpp>

namespace ge
{
    class ShapePropertiesComponent : public Component
    {
    private:
        FloatNotifyProperty x_property;
        FloatNotifyProperty y_property;
        Vec2NotifyProperty position_property;
        FloatNotifyProperty width_property;
        FloatNotifyProperty height_property;
        Vec2NotifyProperty size_property;
        FloatNotifyProperty rotation_property;
    public:
        ShapePropertiesComponent(GameObject *owner);
        FloatNotifyProperty& x();
        FloatNotifyProperty *p_x();
        FloatNotifyProperty& y();
        FloatNotifyProperty *p_y();
        Vec2NotifyProperty& position();
        Vec2NotifyProperty *p_position();
        FloatNotifyProperty& width();
        FloatNotifyProperty *p_width();
        FloatNotifyProperty& height();
        FloatNotifyProperty *p_height();
        Vec2NotifyProperty& size();
        Vec2NotifyProperty *p_size();
        FloatNotifyProperty& rotation();
        FloatNotifyProperty *p_rotation();
    };
}

#endif
