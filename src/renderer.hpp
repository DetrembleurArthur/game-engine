#ifndef __GE_RENDERER_HPP__
#define __GE_RENDERER_HPP__
#include <shader.hpp>
#include <vertex_buffer.hpp>
#include <camera2D.hpp>
#include <transform.hpp>

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
        void draw(float dt, VertexBuffer& vb, Transform& tr);
        void set_camera(Camera2D *camera);
    };
}


#endif
