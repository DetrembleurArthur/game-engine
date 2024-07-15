#include "ge/entity/components/shape_properties_component.hpp"
#include "ge/entity/game_object.hpp"

ge::ShapePropertiesComponent::ShapePropertiesComponent(ge::GameObject *owner) : Component(owner)
{
    x_property.on_change([owner](float x) {
        ge::Transform& tr = *owner;
        tr.set_x(x);
    });
    y_property.on_change([owner](float y) {
        ge::Transform& tr = *owner;
        tr.set_y(y);
    });
    position_property.on_change([owner](glm::vec2 position) {
        ge::Transform& tr = *owner;
        tr.set_position(position);
    });
    position_property.link<float>(&x_property,
        [](const glm::vec2& position) {
            return position.x;
        },
        [owner](const float& x) {
            return glm::vec2(x, owner->get_transform().get_y());
    });
    position_property.link<float>(&y_property,
        [](const glm::vec2& position) {
            return position.y;
        },
        [owner](const float& y) {
            return glm::vec2(owner->get_transform().get_x(), y);
    });
    width_property.on_change([owner](float width) {
        ge::Transform& tr = *owner;
        tr.set_width(width);
    });
    height_property.on_change([owner](float height) {
        ge::Transform& tr = *owner;
        tr.set_height(height);
    });
    size_property.on_change([owner](glm::vec2 size) {
        ge::Transform& tr = *owner;
        tr.set_size(size.x, size.y);
    });
    size_property.link<float>(&width_property,
        [](const glm::vec2& size) {
            return size.x;
        },
        [owner](const float& width) {
            return glm::vec2(width, owner->get_transform().get_height());
    });
    size_property.link<float>(&height_property,
        [](const glm::vec2& size) {
            return size.y;
        },
        [owner](const float& height) {
            return glm::vec2(owner->get_transform().get_width(), height);
    });
    rotation_property.on_change([owner](float rotation) {
        owner->get_transform().set_rotation(rotation);
    });
}

ge::FloatNotifyProperty &ge::ShapePropertiesComponent::x()
{
    return x_property;
}

ge::FloatNotifyProperty *ge::ShapePropertiesComponent::p_x()
{
    return &x_property;
}

ge::FloatNotifyProperty &ge::ShapePropertiesComponent::y()
{
    return y_property;
}

ge::FloatNotifyProperty *ge::ShapePropertiesComponent::p_y()
{
    return &y_property;
}

ge::Vec2NotifyProperty &ge::ShapePropertiesComponent::position()
{
    return position_property;
}

ge::Vec2NotifyProperty *ge::ShapePropertiesComponent::p_position()
{
    return &position_property;
}

ge::FloatNotifyProperty &ge::ShapePropertiesComponent::width()
{
    return width_property;
}

ge::FloatNotifyProperty *ge::ShapePropertiesComponent::p_width()
{
    return &width_property;
}

ge::FloatNotifyProperty &ge::ShapePropertiesComponent::height()
{
    return height_property;
}

ge::FloatNotifyProperty *ge::ShapePropertiesComponent::p_height()
{
    return &height_property;
}

ge::Vec2NotifyProperty &ge::ShapePropertiesComponent::size()
{
    return size_property;
}

ge::Vec2NotifyProperty *ge::ShapePropertiesComponent::p_size()
{
    return &size_property;
}

ge::FloatNotifyProperty &ge::ShapePropertiesComponent::rotation()
{
    return rotation_property;
}

ge::FloatNotifyProperty *ge::ShapePropertiesComponent::p_rotation()
{
    return &rotation_property;
}
