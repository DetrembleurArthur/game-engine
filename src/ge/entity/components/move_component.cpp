#include "ge/entity/components/move_component.hpp"
#include <ge/entity/game_object.hpp>

void ge::MoveComponent::update(float dt)
{
    ge::Transform& tr = owner->get_transform();
    tr.set_position(tr.get_position() + speed * dt);
    speed += accel * dt;
    if((speed.x < 0 ? -speed.x : speed.x) > limit.x)
        speed.x = speed.x < 0 ? -limit.x : limit.x;
    if((speed.y < 0 ? -speed.y : speed.y) > limit.y)
        speed.y = speed.y < 0 ? -limit.y : limit.y;
    tr.set_rotation(tr.get_rotation() + rotation_speed * dt);
    rotation_speed += rotation_accel * dt;
    if((rotation_speed < 0 ? -rotation_speed : rotation_speed) > rotation_limit)
        rotation_speed = rotation_speed < 0 ? -rotation_limit : rotation_limit;
    if(angle_distance > 0)
    {
        angle_accumulator += angle_speed * dt;
        angle_speed += angle_accel * dt;
        if((angle_speed < 0 ? -angle_speed : angle_speed) > angle_limit)
            angle_speed = angle_speed < 0 ? -angle_limit : angle_limit;
        tr.set_angle(angle_target, angle_accumulator, angle_distance);
    }
}

void ge::MoveComponent::toward(glm::vec2 target, glm::vec2 speed)
{
    glm::vec2&& direction = owner->get_transform().get_direction(target);
    this->speed = speed * direction;
}

void ge::MoveComponent::toward_accel(glm::vec2 target, glm::vec2 accel)
{
    glm::vec2&& direction = owner->get_transform().get_direction(target);
    this->accel = accel * direction;
}

void ge::MoveComponent::around(glm::vec2 target, float distance)
{
    angle_target = target;
    angle_distance = distance;
}
