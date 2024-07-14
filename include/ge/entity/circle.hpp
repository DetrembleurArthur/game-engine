#ifndef __GE_CIRCLE_HPP__
#define __GE_CIRCLE_HPP__
#include <ge/entity/drawable.hpp>

namespace ge
{
    class Circle : public ge::Drawable
    {
    private:
        int points=0;
        void init_circle_mesh(float radius, bool tex=false, bool dynamic=false);
    public:
        using Drawable::Drawable;
        Circle(int points, float radius, bool tex=false, bool dynamic=false);
        Circle(int points, const ge::Texture *texture, bool dynamic=false);
        void set_points(int points);
        void set_radius(float radius);
        int get_points() const;
        float get_radius();
        void update_circle_uvs(glm::vec2 uvs_origin, glm::vec2 size);
        void set_texture(const ge::Texture *texture) override;
    };
}

#endif
