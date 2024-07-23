#include "ge/entity/ui/button.hpp"
#include <ge/entity/components/renderer_component.hpp>
#include <ge/entity/components/shape_properties_component.hpp>
#include <ge/entity/components/text_properties_component.hpp>
#include <ge/entity/components/events_components.hpp>
#include <ge/entity/components/color_properties_component.hpp>
#include <ge/core/application.hpp>


ge::Button::Button(int width, int height, bool tex, bool dynamic) : Node()
{
    background = new Rect(width, height, tex, dynamic);
    add(background);
    background->get_component<ge::ColorPropertiesComponent>().color().set(idle_color);
    background->get_component<ge::EventsComponent>().on_mouse_enter([this](auto *e) {
        background->get_component<ge::ColorPropertiesComponent>().color().set(hover_color);
    }).use_collider();
    background->get_component<ge::EventsComponent>().on_mouse_leave([this](auto *e) {
        background->get_component<ge::ColorPropertiesComponent>().color().set(idle_color);
    }).use_collider();
    background->get_component<ge::EventsComponent>().on_mouse_left_pressed([this](auto *e) {
        background->get_component<ge::ColorPropertiesComponent>().color().set(click_color);
    }).use_collider();
    background->get_component<ge::EventsComponent>().on_mouse_left_release([this](auto *z) {
        callback(*this);
        background->get_component<ge::ColorPropertiesComponent>().color().set(idle_color);
    }).use_collider();
}

ge::Rect &ge::Button::get_background()
{
    return *background;
}

ge::Text &ge::Button::get_text()
{
    return *text;
}

void ge::Button::set_text(const std::string &str, ge::Font *font, ge::Renderer *text_renderer)
{
    if(!str.empty())
    {
        if(!text && font && text_renderer)
        {
            text = new ge::Text(str, font);

            text->set_text_align(ge::TextAlign::CENTER);
            text->get_transform().set_center_origin();

            background->get_component<ge::ShapePropertiesComponent>().position()
                .link<glm::vec2>(text->get_component<ge::ShapePropertiesComponent>().p_position(), [this](const glm::vec2& _) {
                    return background->get_transform().get_center_position();
                });
            background->get_component<ge::ShapePropertiesComponent>().height()
                .link<float>(text->get_component<ge::TextPropertiesComponent>().p_text_height(), [](const float &height) {
                    return height * 0.6;
                });
            background->get_component<ge::ColorPropertiesComponent>().color()
                .link<ge::Color>(text->get_component<ge::ColorPropertiesComponent>().p_color(), [](const ge::Color& color) {
                    return ge::Color(1-color.r, 1-color.g, 1-color.b, color.a);
                });

            background->get_component<ge::ShapePropertiesComponent>().height().notify();
            background->get_component<ge::ShapePropertiesComponent>().position().notify();
            background->get_component<ge::ColorPropertiesComponent>().color().notify();
            text->get_component<ge::RendererComponent>().set_renderer(text_renderer);
            add(text);
        }
        else
        {
            text->get_component<ge::TextPropertiesComponent>().text().set(str);
            background->get_component<ge::ShapePropertiesComponent>().height().notify();
            background->get_component<ge::ShapePropertiesComponent>().position().notify();
        }
    }
}

void ge::Button::on_click(std::function<void(ge::Button &)> callback)
{
    this->callback = callback;
}

void ge::Button::set_hover_color(ge::Color color)
{
    hover_color = color;
}

void ge::Button::set_click_color(ge::Color color)
{
    click_color = color;
}

void ge::Button::set_idle_color(ge::Color color)
{
    idle_color = color;
}

void ge::Button::set_position(float x, float y)
{
    background->get_component<ge::ShapePropertiesComponent>().position().set(glm::vec2(x, y));
    background->get_component<ge::ShapePropertiesComponent>().size().notify();
}

void ge::Button::set_size(float width, float height)
{
    background->get_component<ge::ShapePropertiesComponent>().size().set(glm::vec2(width, height));
    background->get_component<ge::ShapePropertiesComponent>().position().notify();
}
