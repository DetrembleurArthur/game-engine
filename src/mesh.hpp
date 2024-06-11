#ifndef __GE_MESH_HPP__
#define __GE_MESH_HPP__
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>


namespace ge
{
    struct MeshLayer
    {
        static MeshLayer DEFAULT_LAYERS[2];
        int elements=3;
        int type=GL_FLOAT;
        size_t size=sizeof(float);
    };

    struct MeshAttribute
    {
        const MeshLayer *layers_ref=nullptr;
        int layers=0;
        void *vertices=nullptr;
        size_t vertices_bytes=0U;
    };

    class Mesh
    {
    private:
        static float RECT_VERTICES[12];
        static float RECT_TEX_VERTICES[20];
        static unsigned RECT_ELEMENTS[6];
    protected:
        unsigned vao=0;
        unsigned vbo=0;
        unsigned ebo=0;
        int draw_policy=GL_STATIC_DRAW;
        size_t elements_number=0;
        int primitive=GL_TRIANGLES;
        int weight=0;
        bool textured=false;
        int attributes=0;
    public:
        Mesh();
        virtual ~Mesh();
        void bind();
        void unbind();
        void create();
        void fill(MeshAttribute *attributes, size_t esize, unsigned *elements, bool textured);
        void set_dynamic(bool value=true);
        void draw();
        void as_triangles();
        void as_points();
        void as_lines();
        void as_line_strip();
        void as_line_loop();
        void as_triangle_strip();
        void as_triangle_fan();
        void set_weight(int weight);
        bool is_textured() const;
        static Mesh *create_rect(bool textured=false);
        static Mesh *create_circle(int points=3, bool textured=false);
    };
}

#endif
