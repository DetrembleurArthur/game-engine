#ifndef __GE_DRAWABLE_HPP__
#define __GE_DRAWABLE_HPP__
#include <ge/entity/game_object.hpp>
#include <ge/graphics/mesh.hpp>
#include <ge/graphics/texture.hpp>
#include <ge/utils/colors.hpp>

namespace ge
{
    class Drawable : public ge::GameObject
    {
    protected:
        Color color;
        Mesh *mesh=nullptr;
        const Texture *texture=nullptr;
    public:
        Drawable();
        virtual ~Drawable();
        void set_color(Color color);
        Color& get_color();
        Mesh *get_mesh();
        const Texture *get_texture();
        void set_texture(const Texture *texture);
    };
}


#endif
