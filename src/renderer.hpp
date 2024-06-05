#ifndef __GE_RENDERER_HPP__
#define __GE_RENDERER_HPP__
#include <shader.hpp>
#include <vertex_buffer.hpp>

namespace ge
{
    class Renderer
    {
    private:
        Shader *shader;
    public:
        Renderer(Shader *shader);
        void begin();
        void end();
        void draw(float dt, VertexBuffer& vb);
    };
}


#endif
