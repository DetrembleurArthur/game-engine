#ifndef __GE_SLIDER_HPP__
#define __GE_SLIDER_HPP__
#include <ge/entity/node.hpp>
#include <ge/entity/rect.hpp>
#include <ge/binding/notify_property.hpp>

namespace ge
{
    class Slider : public Node
    {
    private:
        Rect *bar=nullptr;
        Rect *cursor=nullptr;
        FloatNotifyProperty min_value;
        FloatNotifyProperty max_value;
        FloatNotifyProperty progress_value;
    public:
        Slider(int width, int height, float min_value, float max_value, float current_value, bool tex=false, bool dynamic=false);
        void set_value(float value);
        float get_value();
        FloatNotifyProperty& progress();
        void set_position(float x, float y);
    };
}

#endif

