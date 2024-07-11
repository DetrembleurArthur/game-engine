#ifndef __GE_RENDERER_HPP__
#define __GE_RENDERER_HPP__
#include <ge/graphics/shader.hpp>
#include <ge/graphics/mesh.hpp>
#include <ge/graphics/camera2D.hpp>
#include <ge/entity/transform.hpp>
#include <ge/graphics/texture.hpp>
#include <ge/entity/drawable.hpp>
#include <ge/entity/text.hpp>

namespace ge
{
    class Renderer
    {
    private:
        Shader *shader;
        Camera2D *camera;
    public:
        Renderer(Shader *shader, Camera2D *camera);
        void begin();
        void end();
        void draw_text(float dt, Text *go);
        void draw(float dt, Drawable* go);
        void set_camera(Camera2D *camera);
    };
}


#endif
