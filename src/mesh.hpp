#ifndef __GE_MESH_HPP__
#define __GE_MESH_HPP__
#include <GL/glew.h>
#include <glm/glm.hpp>


namespace ge
{
    class Mesh
    {
    protected:
        unsigned vao=0;
        unsigned vbo=0;
        unsigned ebo=0;
        int draw_policy=GL_STATIC_DRAW;
        size_t elements_number=0;
        int primitive=GL_TRIANGLES;
        glm::vec4 color;
        int weight=0;
    public:
        Mesh();
        virtual ~Mesh();
        glm::vec4& get_color();
        void bind();
        void unbind();
        void create();
        void fill(size_t vsize, float *vertices, size_t esize, unsigned *elements);
        void set_dynamic(bool value=true);
        void draw();
        void as_triangles();
        void as_points();
        void as_lines();
        void as_line_strip();
        void as_line_loop();
        void as_triangle_strip();
        void as_triangle_fan();
        void set_color(const glm::vec4& color);
        void set_weight(int weight);
        static Mesh *create_rect();
        static Mesh *create_circle(int points=3);
    };
}

#endif
