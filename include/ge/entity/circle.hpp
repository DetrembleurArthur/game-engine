#ifndef __GE_CIRCLE_HPP__
#define __GE_CIRCLE_HPP__
#include <ge/entity/drawable.hpp>

namespace ge
{
    class Circle : public ge::Drawable
    {
    private:
        int points=0;
        void init_circle_mesh(float radius);
    public:
        using Drawable::Drawable;
        Circle(int points, float radius);
        Circle(int points, ge::Texture *texture);
        void set_points(int points);
        void set_radius(float radius);
        int get_points() const;
        float get_radius();
    };
}

#endif
