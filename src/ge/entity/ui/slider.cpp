#include "ge/entity/ui/slider.hpp"
#include <ge/entity/components/shape_properties_component.hpp>
#include <ge/entity/components/events_components.hpp>


ge::Slider::Slider(int width, int height, float min, float max, float current_value, bool tex, bool dynamic) : Node()
{
    min_value.set(min);
    max_value.set(max);
    set_value(current_value);

    bar = new ge::Rect(width, height, tex, dynamic);
    bar->set_color(ge::Colors::BLACK);

    cursor = new ge::Rect(height * 3, height * 3, tex, dynamic);
    cursor->set_color(ge::Colors::WHITE);
    cursor->get_transform().set_center_origin();
    cursor->get_component<ge::EventsComponent>().dragging(ge::DragMode::X_AXIS, true);

    cursor->get_component<ge::ShapePropertiesComponent>().x().on_change([this](float x) {
        float xbar = bar->get_transform().get_tl_position().x;
        float wbar = bar->get_transform().get_width();
        if(x < xbar)
            cursor->get_component<ge::ShapePropertiesComponent>().x().set_no_notify(xbar);
        else if(x > xbar + wbar)
            cursor->get_component<ge::ShapePropertiesComponent>().x().set_no_notify(xbar + wbar);
    });
    cursor->get_component<ge::ShapePropertiesComponent>().x()
        .link<float>(&progress_value, [this](float x) {
            float xbar = bar->get_transform().get_tl_position().x;
            float wbar = bar->get_transform().get_width();  
            return (x - xbar) / (wbar);
        });

    bar->get_component<ge::ShapePropertiesComponent>().position()
        .link<glm::vec2>(cursor->get_component<ge::ShapePropertiesComponent>().p_position(), [this](const glm::vec2& _) {
            glm::vec2&& center = bar->get_transform().get_center_position();
            glm::vec2&& left = bar->get_transform().get_tl_position();
            float width = bar->get_transform().get_width();
            return glm::vec2(left.x + width * progress_value.get(), center.y);
        });
    bar->get_component<ge::ShapePropertiesComponent>().position().notify();
    progress_value.on_change([this](float perc) {
        bar->get_component<ge::ShapePropertiesComponent>().position().notify();
        std::cout << perc << std::endl;
    });

    add(bar);
    add(cursor);
}

void ge::Slider::set_value(float value)
{
    if(value < min_value.get())
        value = min_value.get();
    else if(value > max_value.get())
        value = max_value.get();
    progress_value.set((value - min_value.get()) / (max_value.get() - min_value.get()));
}

float ge::Slider::get_value()
{
    return min_value.get() + (max_value.get() - min_value.get()) * progress_value.get();
}

ge::FloatNotifyProperty &ge::Slider::progress()
{
    return progress_value;
}

void ge::Slider::set_position(float x, float y)
{
    bar->get_component<ge::ShapePropertiesComponent>().position().set(glm::vec2(x, y));
}
