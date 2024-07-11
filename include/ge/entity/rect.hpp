#ifndef __GE_RECT_HPP__
#define __GE_RECT_HPP__
#include <ge/entity/drawable.hpp>

namespace ge
{
    class Rect : public ge::Drawable
    {
    private:
        void init_rect_mesh(float width, float height);
    public:
        using Drawable::Drawable;
        Rect(float width, float height);
        Rect(ge::Texture *texture);
    };
}

#endif
