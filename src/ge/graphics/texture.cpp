#include "ge/graphics/texture.hpp"
#include <GL/glew.h>

ge::Texture::Texture(Image &image)
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    auto format = image.get_channels() == 4 ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, image.get().width, image.get().height, 0, format, GL_UNSIGNED_BYTE, image.get().pixels);
    enable_repeat();
    enable_nearest();
}

ge::Texture::~Texture()
{
    glDeleteTextures(1, &id);
}

void ge::Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void ge::Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void ge::Texture::active() const
{
    glActiveTexture(GL_TEXTURE0);
}

void ge::Texture::enable_wrap_param(int param)
{
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param);
    unbind();
}

void ge::Texture::enable_filter_param(int param)
{
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
    unbind();
}

void ge::Texture::enable_linear()
{
    enable_filter_param(GL_LINEAR);
}

void ge::Texture::enable_nearest()
{
    enable_filter_param(GL_NEAREST);
}

void ge::Texture::enable_repeat()
{
    enable_wrap_param(GL_REPEAT);
}

void ge::Texture::enable_mirror()
{
    enable_wrap_param(GL_MIRRORED_REPEAT);
}

void ge::Texture::enable_clamp_to_edge()
{
    enable_wrap_param(GL_CLAMP_TO_EDGE);
}

void ge::Texture::enable_clamp_to_border()
{
    enable_wrap_param(GL_CLAMP_TO_BORDER);
}

glm::uvec2 ge::Texture::get_size() const
{
    bind();
    int width, height;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
    unbind();
    return glm::uvec2(width, height);
}

ge::Texture *ge::Texture::load(const std::string &filename, bool rgb)
{
    Image img(filename);
    img.load(rgb ? 3 : 4);
    Texture *texture = new Texture(img);
    return texture;
}
