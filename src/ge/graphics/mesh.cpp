#include "ge/graphics/mesh.hpp"
#include <GL/glew.h>
#include <cmath>
#include <iostream>

ge::MeshLayer ge::MeshLayer::DEFAULT_LAYERS[2] = {
    { // positions
        .elements=3,
        .type=GL_FLOAT,
        .size=sizeof(float)
    },
    { // tex
        .elements=2,
        .type=GL_FLOAT,
        .size=sizeof(float)
    },
};

float ge::Mesh::RECT_VERTICES[12] = {
        0, 0, 0,
        0, 1, 0,
        1, 1, 0,
        1, 0, 0
};
float ge::Mesh::RECT_TEX_VERTICES[20] = {
        0, 0, 0, 0, 0,
        0, 1, 0, 0, 1,
        1, 1, 0, 1, 1,
        1, 0, 0, 1, 0
};
unsigned ge::Mesh::RECT_ELEMENTS[6] = {
        0, 1, 2,
        0, 2, 3
};

ge::Mesh::Mesh()
{
    create();
}

ge::Mesh::~Mesh()
{
    bind();
    for(int i = 0; i < attributes; i++)
        glDisableVertexAttribArray(i);
    unbind();
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}


void ge::Mesh::bind()
{
    glBindVertexArray(vao);
}

void ge::Mesh::unbind()
{
    glBindVertexArray(0);
}

void ge::Mesh::create()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
}



void ge::Mesh::fill(MeshAttribute *attributes, size_t esize, unsigned *elements, bool textured)
{
    size_t vertex_size = 0U;
    for(int i = 0; i < attributes->layers; i++)
    {
        vertex_size += attributes->layers_ref[i].elements * attributes->layers_ref[i].size;
    }
    bind();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, attributes->vertices_bytes, attributes->vertices, draw_policy);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, esize, elements, draw_policy);
    long long offset = 0;
    for(int i = 0; i < attributes->layers; i++)
    {
        glVertexAttribPointer(i, attributes->layers_ref[i].elements, attributes->layers_ref[i].type, GL_FALSE, vertex_size, (void*)offset);
        glEnableVertexAttribArray(i);
        offset += attributes->layers_ref[i].elements * attributes->layers_ref[i].size;
    }
    unbind();
    glBindVertexArray(0);
    elements_number = esize;
    this->textured = textured;
    this->attributes = attributes->layers;
}

void ge::Mesh::set_dynamic(bool value)
{
    draw_policy = value ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
}

void ge::Mesh::draw()
{
    if(weight)
        glLineWidth(weight);
    bind();
    for(int i = 0; i < attributes; i++)
        glEnableVertexAttribArray(i);
    glDrawElements(primitive, elements_number, GL_UNSIGNED_INT, 0);
    unbind();

}

void ge::Mesh::as_triangles()
{
    primitive = GL_TRIANGLES;
}

void ge::Mesh::as_points()
{
    primitive = GL_POINTS;
}

void ge::Mesh::as_lines()
{
    primitive = GL_LINES;
}

void ge::Mesh::as_line_strip()
{
    primitive = GL_LINE_STRIP;
}

void ge::Mesh::as_line_loop()
{
    primitive = GL_LINE_LOOP;
}

void ge::Mesh::as_triangle_strip()
{
    primitive = GL_TRIANGLE_STRIP;
}

void ge::Mesh::as_triangle_fan()
{
    primitive = GL_TRIANGLE_FAN;
}


void ge::Mesh::set_weight(int weight)
{
    this->weight = weight;
}

bool ge::Mesh::is_textured() const
{
    return textured;
}

ge::Mesh *ge::Mesh::create_rect(bool textured)
{
    MeshAttribute ma = {
        .layers_ref=MeshLayer::DEFAULT_LAYERS,
        .layers=1 + textured,
        .vertices=textured ? Mesh::RECT_TEX_VERTICES : Mesh::RECT_VERTICES,
        .vertices_bytes=textured ? sizeof(Mesh::RECT_TEX_VERTICES) : sizeof(Mesh::RECT_VERTICES)
    };
    Mesh *mesh = new Mesh();
    mesh->fill(&ma, sizeof(Mesh::RECT_ELEMENTS), Mesh::RECT_ELEMENTS, textured);
    return mesh;
}

ge::Mesh *ge::Mesh::create_circle(int points, bool textured)
{
    points = points > 3 ? points : 3;
    float angle = glm::radians(360.0 / points);
    float *vertices = new float[(points + 1) * (3 + 2 * textured)]; //x, y, z, tx, ty
    int vertex_offset = 0;
    vertices[vertex_offset++] = 0.5; // center.x
    vertices[vertex_offset++] = 0.5; // center.y
    vertices[vertex_offset++] = 0;
    if(textured)
    {
        vertices[vertex_offset++] = 0.5;
        vertices[vertex_offset++] = 0.5;
    }
    for(int i = 0; i < points; i++)
    {
        auto x = vertices[0] + (0.5 * std::sin(angle * i));
        auto y = vertices[1] + (-0.5 * std::cos(angle * i));
        vertices[vertex_offset++] = x;
        vertices[vertex_offset++] = y;
        vertices[vertex_offset++] = 0;
        if(textured)
        {
            vertices[vertex_offset++] = x;
            vertices[vertex_offset++] = y;
        }
    }
    unsigned *elements = new unsigned[points * 3];
    int element_offset = 0;
    for(int i = 0; i < points - 1; i++)
    {
        elements[element_offset++] = 0;
        elements[element_offset++] = i + 1;
        elements[element_offset++] = i + 2;
    }
    elements[element_offset++] = 0;
    elements[element_offset++] = points;
    elements[element_offset++] = 1;
    MeshAttribute ma = {
        .layers_ref=MeshLayer::DEFAULT_LAYERS,
        .layers=1 + textured,
        .vertices=vertices,
        .vertices_bytes=(points + 1) * (3 + 2 * textured) * sizeof(float)
    };
    Mesh *mesh = new Mesh();
    mesh->fill(&ma, points * 3 * 4, elements, textured); // *4 because it is in number of bytes
    delete[] vertices;
    delete[] elements;
    return mesh;
}
