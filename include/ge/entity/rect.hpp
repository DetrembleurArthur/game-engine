#ifndef __GE_RECT_HPP__
#define __GE_RECT_HPP__
#include <ge/entity/drawable.hpp>

namespace ge
{
    class Rect : public ge::Drawable
    {
    private:
        void init_rect_mesh(float width, float height, bool tex=false, bool dynamic=false);
    public:
        Rect();
        Rect(float width, float height, bool tex=false, bool dynamic=false);
        Rect(ge::Texture *texture, bool dynamic=false);
        void set_texture(const ge::Texture *texture) override;
        void update_uvs(glm::vec2 uvs_origin, glm::vec2 size) override;
        void move_tex(glm::vec2 delta, bool normalized=false);
    };
}

#endif
