#include "ge/entity/transform.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <ge/utils/log.hpp>

ge::Transform::Transform() : size(1, 1, 1), position(0, 0, 0), rotation(0, 0, 0), origin(0, 0, 0), model(glm::identity<glm::mat4>())
{
}

glm::mat4 ge::Transform::get_model()
{
    if(dirty)
    {
        model = glm::identity<glm::mat4>();
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
        model = glm::translate(model, -origin);
        model = glm::scale(model, size);
        dirty = false;
    }
    return model;
}

void ge::Transform::set_size(float width, float height)
{
    width = std::fmax(width, 1e-10f);
    height = std::fmax(height, 1e-10f);
    origin = origin * glm::vec3(width / size.x, height / size.y, 1);
    size.x = width;
    size.y = height;
    dirty = true;
}

void ge::Transform::set_width(float width)
{
    set_size(width, size.y);
}

void ge::Transform::set_height(float height)
{
    set_size(size.x, height);
}

glm::vec2 ge::Transform::get_size()
{
    return glm::vec2(size);
}

float ge::Transform::get_width()
{
    return size.x;
}

float ge::Transform::get_height()
{
    return size.y;
}

void ge::Transform::set_position(float x, float y)
{
    position.x = x;
    position.y = y;
    dirty = true;
}

void ge::Transform::set_position(glm::vec2 pos)
{
    set_position(pos.x, pos.y);
}

void ge::Transform::set_x(float x)
{
    position.x = x;
    dirty = true;
}

void ge::Transform::set_y(float y)
{
    position.y = y;
    dirty = true;
}

glm::vec2 ge::Transform::get_position()
{
    return glm::vec2(position);
}

float ge::Transform::get_x()
{
    return position.x;
}

float ge::Transform::get_y()
{
    return position.y;
}

void ge::Transform::set_origin(float x, float y)
{
    origin.x = x;
    origin.y = y;
    origin.z = 0;
    dirty = true;
}

void ge::Transform::set_tl_origin()
{
    set_origin(0, 0);
}

void ge::Transform::set_tr_origin()
{
    set_origin(size.x, 0);
}

void ge::Transform::set_br_origin()
{
    set_origin(size.x, size.y);
}

void ge::Transform::set_bl_origin()
{
    set_origin(0, size.y);
}

void ge::Transform::set_center_origin()
{
    set_origin(size.x / 2, size.y / 2);
}

void ge::Transform::set_origin_position(glm::vec2 origin, glm::vec2 position)
{
    set_position(
        position.x + (this->origin.x - origin.x),
        position.y + (this->origin.y - origin.y)
    );
}

glm::vec2 ge::Transform::get_origin_position(glm::vec2 origin)
{
    return glm::vec2(position) - (glm::vec2(this->origin) -  origin);
}

glm::vec2 ge::Transform::get_tl_position()
{
    return get_origin_position(glm::vec2(0, 0));
}

glm::vec2 ge::Transform::get_tr_position()
{
    return get_origin_position(glm::vec2(size.x, 0));
}

glm::vec2 ge::Transform::get_bl_position()
{
    return get_origin_position(glm::vec2(0, size.y));
}

glm::vec2 ge::Transform::get_br_position()
{
    return get_origin_position(glm::vec2(size.x, size.y));
}

glm::vec2 ge::Transform::get_center_position()
{
    return get_origin_position(glm::vec2(size.x / 2, size.y / 2));
}

void ge::Transform::set_tl_position(glm::vec2 position)
{
    set_origin_position(glm::vec2(0, 0), position);
}

void ge::Transform::set_tr_position(glm::vec2 position)
{
    set_origin_position(glm::vec2(size.x, 0), position);
}

void ge::Transform::set_bl_position(glm::vec2 position)
{
    set_origin_position(glm::vec2(0, size.y), position);
}

void ge::Transform::set_br_position(glm::vec2 position)
{
    set_origin_position(glm::vec2(size.x, size.y), position);
}

void ge::Transform::set_center_position(glm::vec2 position)
{
    set_origin_position(glm::vec2(size.x / 2, size.y / 2), position);
}

float ge::Transform::get_angle(glm::vec2 target)
{
    return glm::degrees(glm::atan(-(position.y - target.y), -(position.x - target.x)));
}

float ge::Transform::get_rotation()
{
    return rotation.z;
}

glm::vec2 ge::Transform::get_direction(glm::vec2 target)
{
    return glm::normalize(target - glm::vec2(position));
}

void ge::Transform::set_rotation(float angle)
{
    rotation.z = angle;
    dirty = true;
}

// rotation around target by angle degreess (based on the position of the object)
void ge::Transform::set_relative_angle(glm::vec2 target, float angle)
{
    angle = glm::radians(angle);
    glm::vec2 pos = glm::vec2(position) - target;
    pos = glm::vec2(pos.x * cos(angle) - pos.y * sin(angle), pos.x * sin(angle) + pos.y * cos(angle));
    pos += target;
    position.x = pos.x;
    position.y = pos.y;
    dirty = true;
}

// rotation around target by angle degreess at a certain distance (based on the position of the object)
void ge::Transform::set_relative_angle(glm::vec2 target, float angle, float distance)
{
    angle = glm::radians(angle);
    std::cout << "angle: " << angle << std::endl;
    glm::vec2 pos = glm::vec2(position) - target;
    pos = glm::normalize(pos)*glm::vec2(distance,distance);
    pos = glm::vec2(pos.x * cos(angle) - pos.y * sin(angle), pos.x * sin(angle) + pos.y * cos(angle));
    pos += target;
    position.x = pos.x;
    position.y = pos.y;
    dirty = true;
}

// set object position at "angle" degrees of the target at "distance" pixels
void ge::Transform::set_angle(glm::vec2 target, float angle, float distance)
{
    // based on dist = sqrt(2x^2)
    angle = glm::radians(angle-45);
    distance = (distance * sqrtf(2.0)) / 2;
    glm::vec2 pos = glm::vec2(distance, distance);
    pos = glm::vec2(pos.x * cos(angle) - pos.y * sin(angle), pos.x * sin(angle) + pos.y * cos(angle));
    pos += target;
    position.x = pos.x;
    position.y = pos.y;
    dirty = true;
}

float ge::Transform::get_distance(glm::vec2 target)
{
    return glm::distance(get_center_position(), target);
}

void ge::Transform::set_dirty(bool value)
{
    dirty = value;
}

bool ge::Transform::is_dirty() const
{
    return dirty;
}

bool ge::Transform::contains(glm::vec2 point)
{
    auto&& tl = get_tl_position();
    return point.x >= tl.x && point.x <= tl.x + size.x and point.y >= tl.y && point.y <= tl.y + size.y;
}

glm::vec2 ge::Transform::get_origin()
{
    return glm::vec2(origin);
}
