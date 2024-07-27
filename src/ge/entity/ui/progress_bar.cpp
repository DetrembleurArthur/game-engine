#include "ge/entity/ui/progress_bar.hpp"
#include <ge/entity/components/shape_properties_component.hpp>
#include <ge/entity/components/renderer_component.hpp>
#include <ge/entity/components/color_properties_component.hpp>
#include <ge/entity/components/text_properties_component.hpp>
#include <iostream>


ge::ProgressBar::ProgressBar(float min, float max, float current_perc, bool vertical, bool center_progression) : Node()
{
    this->vertical = vertical;
    min_value.set(min);
    max_value.set(max);
    min_value.link<float>(&progress_value, [this](float min) {
        return (current_value.get() - min) / (max_value.get() - min);
    });
    max_value.link<float>(&progress_value, [this](float max) {
        return (current_value.get() - min_value.get()) / (max - min_value.get());
    });
    progress_value.link<float>(&current_value, [this](float perc) {
        return min_value.get() + (max_value.get() - min_value.get()) * perc;
    }, [this](float value) {
        return (value - min_value.get()) / (max_value.get() - min_value.get());
    });
    

    background = new Rect(300, 80);
    background->set_color(ge::Colors::BLACK);

    foreground = new Rect(100, 80);
    if(center_progression)
        foreground->get_transform().set_center_origin();

    progress_value.link<Color>(foreground->get_component<ge::ColorPropertiesComponent>().p_color(), [this](float perc) {
        return min_color + (max_color - min_color) * perc;
    });


    background->get_component<ge::ShapePropertiesComponent>().position()
        .link<glm::vec2>(foreground->get_component<ge::ShapePropertiesComponent>().p_position(), [this, center_progression](glm::vec2 pos) {
            return center_progression ? background->get_transform().get_center_position() : background->get_transform().get_tl_position() + border;
        });
    if(vertical)
    {
        background->get_component<ge::ShapePropertiesComponent>().width()
            .link<float>(foreground->get_component<ge::ShapePropertiesComponent>().p_width(), [this](float width) {
                return width - border.x * 2;
            });
        progress_value.link<float>(foreground->get_component<ge::ShapePropertiesComponent>().p_height(), [this](float perc) {
            return (background->get_transform().get_height() - border.y * 2) * perc;
        });
        background->get_component<ge::ShapePropertiesComponent>().width().notify();
    }
    else
    {
        background->get_component<ge::ShapePropertiesComponent>().height()
            .link<float>(foreground->get_component<ge::ShapePropertiesComponent>().p_height(), [this](float height) {
                return height - border.y * 2;
            });
        progress_value.link<float>(foreground->get_component<ge::ShapePropertiesComponent>().p_width(), [this](float perc) {
            return (background->get_transform().get_width() - border.x * 2) * perc;
        });
        background->get_component<ge::ShapePropertiesComponent>().height().notify();
    }
    
    
    progress_value.set(current_perc);
    background->get_component<ge::ShapePropertiesComponent>().position().notify();
    add(background);
    add(foreground);
}

void ge::ProgressBar::set_value(float value)
{
    if(value < min_value.get())
        value = min_value.get();
    else if(value > max_value.get())
        value = max_value.get();
    current_value.set(value);
}

float ge::ProgressBar::get_value()
{
    return current_value.get();
}

void ge::ProgressBar::set_position(float x, float y)
{
    background->get_component<ge::ShapePropertiesComponent>().position().set(glm::vec2(x, y));
}

void ge::ProgressBar::set_size(float width, float height)
{
    background->get_component<ge::ShapePropertiesComponent>().size().set(glm::vec2(width, height));
    background->get_component<ge::ShapePropertiesComponent>().position().notify();
    progress_value.notify();
}

void ge::ProgressBar::set_border(float xb, float yb)
{
    border.x = xb;
    border.y = yb;
    background->get_component<ge::ShapePropertiesComponent>().size().notify();
}

ge::Rect &ge::ProgressBar::get_root()
{
    return *background;
}

void ge::ProgressBar::enable_text(ge::Font *font, ge::Renderer *text_renderer, bool percentage_view)
{
    if(!text && font && text_renderer)
    {
        text = new ge::Text("", font);

        text->set_text_align(ge::TextAlign::CENTER);
        text->get_transform().set_center_origin();

        background->get_component<ge::ShapePropertiesComponent>().position()
            .link<glm::vec2>(text->get_component<ge::ShapePropertiesComponent>().p_position(), [this](const glm::vec2& _) {
                return background->get_transform().get_center_position();
            });
        if(!vertical)
        {
            background->get_component<ge::ShapePropertiesComponent>().height()
            .link<float>(text->get_component<ge::TextPropertiesComponent>().p_text_height(), [](const float &height) {
                return height * 0.6;
            });
            background->get_component<ge::ShapePropertiesComponent>().height().notify();
        }
        else
        {
            background->get_component<ge::ShapePropertiesComponent>().width()
            .link<float>(text->get_component<ge::TextPropertiesComponent>().p_text_width(), [](const float &width) {
                return width * 0.6;
            });
            background->get_component<ge::ShapePropertiesComponent>().width().notify();
        }
        background->get_component<ge::ShapePropertiesComponent>().position().notify();
        text->get_component<ge::RendererComponent>().set_renderer(text_renderer);
        add(text);
        progress_value.link<std::string>(text->get_component<ge::TextPropertiesComponent>().p_text(), [this, percentage_view](float perc) {
            if(percentage_view)
            {
                return std::to_string((int)(perc*100)) + "%";
            }
            return std::to_string((int)current_value.get()) + " / " + std::to_string((int)max_value.get());
        });
        progress_value.notify();
    }
}
