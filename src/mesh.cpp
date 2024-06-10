#include "mesh.hpp"
#include <GL/glew.h>
#include <cmath>
#include <iostream>

ge::Mesh::Mesh() : color(0, 0, 0, 1)
{
    create();
}

ge::Mesh::~Mesh()
{
    bind();
    glDisableVertexAttribArray(0);
    if(textured)
        glDisableVertexAttribArray(1);
    unbind();
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

glm::vec4 &ge::Mesh::get_color()
{
    return color;
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

void ge::Mesh::fill(size_t vsize, float *vertices, size_t esize, unsigned *elements, bool textured)
{
    bind();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vsize, vertices, draw_policy);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, esize, elements, draw_policy);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 2 * textured) * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    this->textured = textured;
    if(textured)
    {
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    unbind();
    glBindVertexArray(0);
    elements_number = esize;
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
    glEnableVertexAttribArray(0);
    if(textured)
        glEnableVertexAttribArray(1);
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

void ge::Mesh::set_color(const glm::vec4 &color)
{
    this->color = color;
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
    float vertices[] = {
        0, 0, 0,
        0, 1, 0,
        1, 1, 0,
        1, 0, 0
    };
    float tex_vertices[] = {
        0, 0, 0, 0, 0,
        0, 1, 0, 0, 1,
        1, 1, 0, 1, 1,
        1, 0, 0, 1, 0
    };
    unsigned elements[] = {
        0, 1, 2,
        0, 2, 3
    };
    Mesh *mesh = new Mesh();
    if(textured)
        mesh->fill(sizeof(tex_vertices), tex_vertices, sizeof(elements), elements, textured);
    else
        mesh->fill(sizeof(vertices), vertices, sizeof(elements), elements, textured);
    return mesh;
}

ge::Mesh *ge::Mesh::create_circle(int points, bool textured)
{
    points = points > 3 ? points : 3;
    float angle = glm::radians(360.0 / points);
    float *vertices = new float[(points + 1) * 5]; //x, y, z, tx, ty
    vertices[0] = 0.5; // center.x
    vertices[1] = 0.5; // center.y
    vertices[2] = 0;
    vertices[3] = 0.5;
    vertices[4] = 0.5;
    int vertex_offset = 5;
    for(int i = 0; i < points; i++)
    {
        auto x = vertices[0] + (0.5 * std::sin(angle * i));
        auto y = vertices[1] + (-0.5 * std::cos(angle * i));
        vertices[vertex_offset++] = x;
        vertices[vertex_offset++] = y;
        vertices[vertex_offset++] = 0;
        vertices[vertex_offset++] = x;
        vertices[vertex_offset++] = y;
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
    Mesh *mesh = new Mesh();
    mesh->fill((points + 1) * 5 * 4, vertices, points * 3 * 4, elements, textured); // *4 because it is in number of bytes
    delete[] vertices;
    delete[] elements;
    return mesh;
}
