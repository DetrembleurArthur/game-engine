#include "vertex_buffer.hpp"

ge::VertexBuffer::VertexBuffer() : color(0, 0, 0, 1)
{
    create();
}

ge::VertexBuffer::~VertexBuffer()
{
    bind();
    glDisableVertexAttribArray(0);
    unbind();
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

glm::vec4 &ge::VertexBuffer::get_color()
{
    return color;
}

void ge::VertexBuffer::bind()
{
    glBindVertexArray(vao);
}

void ge::VertexBuffer::unbind()
{
    glBindVertexArray(0);
}

void ge::VertexBuffer::create()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
}

void ge::VertexBuffer::fill(size_t vsize, float *vertices, size_t esize, unsigned *elements)
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

void ge::VertexBuffer::set_dynamic(bool value)
{
    draw_policy = value ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
}

void ge::VertexBuffer::draw()
{
    bind();
    glDrawElements(primitive, elements_number, GL_UNSIGNED_INT, 0);
    unbind();
}

void ge::VertexBuffer::as_triangles()
{
    primitive = GL_TRIANGLES;
}

void ge::VertexBuffer::as_points()
{
    primitive = GL_POINTS;
}

void ge::VertexBuffer::as_lines()
{
    primitive = GL_LINES;
}

void ge::VertexBuffer::as_line_strip()
{
    primitive = GL_LINE_STRIP;
}

void ge::VertexBuffer::as_line_loop()
{
    primitive = GL_LINE_LOOP;
}

void ge::VertexBuffer::as_triangle_strip()
{
    primitive = GL_TRIANGLE_STRIP;
}

void ge::VertexBuffer::as_triangle_fan()
{
    primitive = GL_TRIANGLE_FAN;
}

void ge::VertexBuffer::set_color(const glm::vec4 &color)
{
    this->color = color;
}
