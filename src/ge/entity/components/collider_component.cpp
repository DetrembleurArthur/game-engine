#include "ge/entity/components/collider_component.hpp"
#include <ge/entity/game_object.hpp>
#include <ge/utils/utils.hpp>



ge::ColliderComponent::ColliderComponent(GameObject *owner) : Component(owner)
{
    Transform& tr = *owner;
    collider.dx = 0;
    collider.dy = 0;
    collider.width = tr.get_width();
    collider.height = tr.get_height();
    normalize_collider();
    update_collider();
}

void ge::ColliderComponent::update_collider()
{
    Transform& tr = *owner;
    float angle = glm::radians(tr.get_rotation());

    collider.tl = glm::vec2(collider.dxf * tr.get_width(), collider.dyf * tr.get_height()) - tr.get_origin();
    collider.tl = glm::vec2(collider.tl.x * cos(angle) - collider.tl.y * sin(angle), collider.tl.x * sin(angle) + collider.tl.y * cos(angle));
    collider.tl += tr.get_position();

    collider.tr = glm::vec2(collider.dxf * tr.get_width() + tr.get_width() * collider.wf, collider.dyf * tr.get_height()) - tr.get_origin();
    collider.tr = glm::vec2(collider.tr.x * cos(angle) - collider.tr.y * sin(angle), collider.tr.x * sin(angle) + collider.tr.y * cos(angle));
    collider.tr += tr.get_position();

    collider.br = glm::vec2(collider.dxf * tr.get_width() + tr.get_width() * collider.wf, collider.dyf * tr.get_height() + tr.get_height() * collider.hf) - tr.get_origin();
    collider.br = glm::vec2(collider.br.x * cos(angle) - collider.br.y * sin(angle), collider.br.x * sin(angle) + collider.br.y * cos(angle));
    collider.br += tr.get_position();

    collider.bl = glm::vec2(collider.dxf * tr.get_width(), collider.dyf * tr.get_height() + tr.get_height() * collider.hf) - tr.get_origin();
    collider.bl = glm::vec2(collider.bl.x * cos(angle) - collider.bl.y * sin(angle), collider.bl.x * sin(angle) + collider.bl.y * cos(angle));
    collider.bl += tr.get_position();


    collider.x = collider.tl.x;
    collider.y = collider.tl.y;
    collider.angle = tr.get_rotation();
}

ge::Collider &ge::ColliderComponent::get_collider()
{
    update_collider();
    return collider;
}

void ge::ColliderComponent::normalize_collider()
{
    Transform& tr = *owner;
    collider.dxf = collider.dx / tr.get_width();
    collider.dyf = collider.dy / tr.get_height();
    collider.wf = collider.width / tr.get_width();
    collider.hf = collider.height / tr.get_height();
}

void ge::ColliderComponent::update_rendered_collider(ge::Transform *rect)
{
    Collider& collider = get_collider();
    rect->set_position(collider.x, collider.y);
    rect->set_rotation(collider.angle);
    rect->set_size(collider.wf * owner->get_transform().get_width(), collider.hf* owner->get_transform().get_height());
}

bool ge::ColliderComponent::contains(glm::vec2 pos)
{
    Collider& collider = get_collider();
    pos = utils::rotate_around(pos, glm::vec2(collider.x, collider.y), -collider.angle);
    return pos.x >= collider.x && pos.x <= collider.x + collider.wf * owner->get_transform().get_width() && pos.y >= collider.y && pos.y <= collider.y + collider.hf* owner->get_transform().get_height();
}

bool ge::ColliderComponent::contains(ColliderComponent &other)
{
    Collider& collider = get_collider();
    float width =  collider.wf * owner->get_transform().get_width();
    float height = collider.hf * owner->get_transform().get_height();
    Collider& other_collider = other.get_collider();
    return other.contains(collider.tl) || other.contains(collider.tr) || other.contains(collider.br) || other.contains(collider.bl) ||
        contains(other_collider.tl) || contains(other_collider.tr) || contains(other_collider.br) || contains(other_collider.bl);
}

bool ge::ColliderComponent::straight_contains(ColliderComponent &other)
{
    Collider& rect1 = get_collider();
    glm::vec2&& size1 = get_collider_size();
    Collider& rect2 = other.get_collider();
    glm::vec2&& size2 = other.get_collider_size();
    return (rect1.x < rect2.x + size2.x && 
        rect1.x + size1.x > rect2.x && 
        rect1.y < rect2.y + size2.y && 
        rect1.y + size1.y > rect2.y);
}

void ge::ColliderComponent::fit_collider(glm::vec2 factors, glm::vec2 dfactors)
{
    collider.width = owner->get_transform().get_width() * factors.x;
    collider.height = owner->get_transform().get_height() * factors.y;
    collider.dx = (owner->get_transform().get_width() - collider.width) * dfactors.x;
    collider.dy = (owner->get_transform().get_height() - collider.height) * dfactors.y;
    normalize_collider();
    update_collider();
}

glm::vec2 ge::ColliderComponent::get_collider_size()
{
    Collider& collider = get_collider();
    float width =  collider.wf * owner->get_transform().get_width();
    float height = collider.hf * owner->get_transform().get_height();
    return glm::vec2(width, height);
}

glm::vec2 ge::ColliderComponent::resolve_straight_collision(ColliderComponent &other)
{
    Collider& collider = get_collider();
    glm::vec2&& size = get_collider_size();
    Collider& other_collider = other.get_collider();
    glm::vec2&& other_size = other.get_collider_size();
    float overlapX1 = collider.x + size.x - other_collider.x;
    float overlapX2 = other_collider.x + other_size.x - collider.x;
    float overlapY1 = collider.y + size.y - other_collider.y;
    float overlapY2 = other_collider.y + other_size.y - collider.y;

    float overlapX = std::min(overlapX1, overlapX2);
    float overlapY = std::min(overlapY1, overlapY2);
    glm::vec2 move(0, 0);
    if (overlapX < overlapY)
    {
        if (overlapX1 < overlapX2)
        {
            move.x = -overlapX;
        } else
        {
            move.x = overlapX;
        }
    } else
    {
        if (overlapY1 < overlapY2)
        {
            move.y = -overlapY;
        } else
        {
            move.y = overlapY;
        }
    }
    return move;
}
