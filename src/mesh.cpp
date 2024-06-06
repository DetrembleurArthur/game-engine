#include "mesh.hpp"
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

void ge::Mesh::fill(size_t vsize, float *vertices, size_t esize, unsigned *elements)
{
    bind();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vsize, vertices, draw_policy);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, esize, elements, draw_policy);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
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

ge::Mesh *ge::Mesh::create_rect()
{
    float vertices[] = {
        0, 0, 0,
        0, 1, 0,
        1, 1, 0,
        1, 0, 0
    };
    unsigned elements[] = {
        0, 1, 2,
        0, 2, 3
    };
    Mesh *mesh = new Mesh();
    mesh->fill(sizeof(vertices), vertices, sizeof(elements), elements);
    return mesh;
}

ge::Mesh *ge::Mesh::create_circle(int points)
{
    points = points > 3 ? points : 3;
    float angle = glm::radians(360.0 / points);
    float *vertices = new float[(points + 1) * 3]; //x, y, z
    vertices[0] = 0.5; // center.x
    vertices[1] = 0.5; // center.y
    vertices[2] = 0;
    int vertex_offset = 3;
    for(int i = 0; i < points; i++)
    {
        vertices[vertex_offset++] = vertices[0] + (0.5 * std::sin(angle * i));
        vertices[vertex_offset++] = vertices[1] + (-0.5 * std::cos(angle * i));
        std::cout << vertices[vertex_offset-2] << ", " << vertices[vertex_offset-1] << std::endl;
        vertices[vertex_offset++] = 0;
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
    mesh->fill((points + 1) * 3 * 4, vertices, points * 3 * 4, elements); // *4 because it is in number of bytes
    delete[] vertices;
    delete[] elements;
    return mesh;
}
