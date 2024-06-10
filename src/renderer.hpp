#ifndef __GE_RENDERER_HPP__
#define __GE_RENDERER_HPP__
#include <shader.hpp>
#include <mesh.hpp>
#include <camera2D.hpp>
#include <transform.hpp>
#include <texture.hpp>
#include <game_object.hpp>

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
