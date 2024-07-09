#ifndef __GE_RENDERER_HPP__
#define __GE_RENDERER_HPP__
#include <ge/graphics/shader.hpp>
#include <ge/graphics/mesh.hpp>
#include <ge/graphics/camera2D.hpp>
#include <ge/entity/transform.hpp>
#include <ge/graphics/texture.hpp>
#include <ge/entity/game_object.hpp>

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
        void draw(float dt, GameObject& go);
        void set_camera(Camera2D *camera);
    };
}


#endif
