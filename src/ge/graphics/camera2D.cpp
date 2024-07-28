#include "ge/graphics/camera2D.hpp"
#include <ge/core/application.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ge/utils/log.hpp>

ge::Camera2D::Camera2D() : Camera2D(Ortho())
{
    update_ortho();
    log("camera setup: " + std::to_string(ortho.left) + " " + std::to_string(ortho.right) + " " + std::to_string(ortho.bottom) + " " + std::to_string(ortho.up));
}

ge::Camera2D::Camera2D(const Ortho &ortho) : zoom(1, 1, 1), ortho(ortho), projection(1), view(1), position(0, 0)
{
}

ge::Camera2D::~Camera2D()
{
    log("destroy camera");

}

void ge::Camera2D::update_ortho()
{
    ortho.left = Application::get().get_viewport().x;
    ortho.right = Application::get().get_viewport().z;
    ortho.bottom = Application::get().get_viewport().w;
    ortho.up = Application::get().get_viewport().y;
    log("camera update: " + std::to_string(ortho.left) + " " + std::to_string(ortho.right) + " " + std::to_string(ortho.bottom) + " " + std::to_string(ortho.up));
}

void ge::Camera2D::update_view()
{
    view = glm::identity<glm::mat4>();
    view = glm::lookAt(glm::vec3(position.x, position.y, 20),
                       glm::vec3(0, 0, -1) + glm::vec3(position.x, position.y, 0),
                       glm::vec3(0, 1, 0));
    glm::vec3 scale_center(position.x + ortho.right / 2, position.y + ortho.bottom / 2, 0);
    view = glm::translate(view, scale_center);
    view = glm::scale(view, zoom);
    view = glm::rotate(view, glm::radians(rotation), glm::vec3(0, 0, 1));

    view = glm::translate(view, -scale_center);

}

glm::vec2 ge::Camera2D::focus(glm::vec2 focus_position)
{
    glm::vec2 old = position;
    position = focus_position - glm::vec2(ortho.right / 2, ortho.bottom / 2);
    return position-old;
}

void ge::Camera2D::set_rotation(float angle)
{
    rotation = angle;
}

glm::mat4 &ge::Camera2D::get_projection()
{
    return projection;
}

glm::mat4 &ge::Camera2D::get_view()
{
    return view;
}

glm::vec2 &ge::Camera2D::get_position()
{
    return position;
}

glm::vec3 &ge::Camera2D::get_zoom()
{
    return zoom;
}

float ge::Camera2D::get_rotation()
{
    return rotation;
}

void ge::Camera2D::update_projection()
{
    projection = glm::identity<glm::mat4>();
    projection = glm::ortho(ortho.left, ortho.right, ortho.bottom, ortho.up, 0.0f, 100.0f);
}
