#ifndef __GE_PROGRESS_BAR_HPP__
#define __GE_PROGRESS_BAR_HPP__
#include <ge/entity/node.hpp>
#include <ge/binding/notify_property.hpp>
#include <ge/entity/rect.hpp>
#include <ge/entity/text.hpp>
#include <ge/tween/tween_functions.hpp>
#include <ge/graphics/renderer.hpp>

namespace ge
{
    class ProgressBar : public Node
    {
    private:
        FloatNotifyProperty min_value;
        FloatNotifyProperty max_value;
        FloatNotifyProperty current_value;
        FloatNotifyProperty progress_value;
        Color min_color=Colors::RED;
        Color max_color=Colors::GREEN;
        std::function<float(float)> tween_function=tweenf::linear;
        glm::vec2 border=glm::vec2(0, 0);
        Rect *background=nullptr;
        Rect *foreground=nullptr;
        Text *text=nullptr;
        bool vertical=false;
    public:
        ProgressBar(float min, float max, float current_perc=0, bool vertical=false, bool center_progression=false);
        void set_value(float value);
        float get_value();
        void set_position(float x, float y);
        void set_size(float width, float height);
        void set_border(float xb, float yb);
        ge::Rect& get_root();
        void enable_text(ge::Font *font=nullptr, ge::Renderer *text_renderer=nullptr, bool percentage_view=false);
    };
}

#endif

