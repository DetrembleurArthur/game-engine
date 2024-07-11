#include "ge/graphics/text/font.hpp"
#include <ge/utils/log.hpp>
#include <cstring>
#include <vector>
#include <fstream>

FT_Library ge::Font::ft;

void ge::Font::init()
{
    if(FT_Init_FreeType(&ge::Font::ft))
    {
        log("font library initialisation failed", ge::LogLevels::ERROR);
        return;
    }
    log("font library initialisation success", ge::LogLevels::FONT);
}

void ge::Font::done()
{
    FT_Done_FreeType(ge::Font::ft);
    log("font library done", ge::LogLevels::FONT);
}

ge::Font::Font(const std::string &filename, int font_size)
{
    const int padding=10;
    if(FT_New_Face(Font::ft, filename.c_str(), 0, &face))
    {
        log("font '" + filename + "' can not be loaded", ge::LogLevels::ERROR);
        return;
    }
    set_font_size(font_size);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    std::vector<std::pair<unsigned char *, Glyph>> buffers;
    glm::ivec2 offsets(0, 0);
    glm::ivec2 max_size(0, 0);
    for(unsigned char c = 0; c < 128; c++)
    {
        if(FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            log("can not load '" + std::to_string(c) + "' char in font " + filename, LogLevels::WARNING);
            continue;
        }
        unsigned char *buffer = new unsigned char[face->glyph->bitmap.rows * face->glyph->bitmap.width];
        std::memcpy(buffer, face->glyph->bitmap.buffer,face->glyph->bitmap.rows * face->glyph->bitmap.width);
        Glyph glyph = {
            //.texture=new Texture(face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer),
            .size=glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            .bearing=glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            .advance=static_cast<unsigned>(face->glyph->advance.x),
            .tex_offset=offsets
        };
        buffers.push_back(std::pair<unsigned char *, Glyph>(buffer, glyph));
        glyphs.insert(std::pair<char, Glyph>(c, glyph));
        offsets += glm::ivec2(glyph.size.x + padding, 0);
        max_size.x += glyph.size.x;
        max_size.y = std::max(max_size.y, glyph.size.y);
    }
    max_size.x += padding * (buffers.size() - 1);
    const int buffer_size = max_size.x * max_size.y;
    unsigned char *texture_buffer = new unsigned char[buffer_size];
    std::fill(texture_buffer, texture_buffer + buffer_size, 0);
    offsets.x = 0;
    offsets.y = 0;
    int buffer_counter = 0;
    for(std::pair<unsigned char *, Glyph>& pair : buffers)
    {
        unsigned char *buffer = pair.first;
        Glyph& glyph = pair.second;
        for(int i = offsets.y; i < offsets.y + glyph.size.y; i++)
        {
            for(int j = offsets.x; j < offsets.x + glyph.size.x; j++)
            {
                texture_buffer[i * max_size.x + j + padding * buffer_counter] = buffer[(i - offsets.y) * glyph.size.x + (j - offsets.x)];
            }
        }
        offsets.x += glyph.size.x;
        delete[] buffer;
        buffer_counter++;
    }
    texture = new Texture(max_size.x, max_size.y, texture_buffer);
    /*std::ofstream file("./res/fonts/texture_map/"+ std::to_string(rand()) + "_map.pgm");
    auto s = std::string("P2 ") + std::to_string(max_size.x) + " " + std::to_string(max_size.y) + " 255\n";
    file.write(s.c_str(), s.size());
    for(int i = 0; i < max_size.x * max_size.y; i++)
    {
        s = std::to_string((unsigned)texture_buffer[i]) + " ";
        file.write(s.c_str(), s.size());
    }
    file.close();*/
    delete[] texture_buffer;


    log("font '" + filename + "' loaded", ge::LogLevels::FONT);
}

ge::Font::~Font()
{
    glyphs.clear();
    if(texture)
        delete texture;
    FT_Done_Face(face);
    log("font done", ge::LogLevels::FONT);
}

void ge::Font::set_font_size(int size)
{
    if(FT_Set_Pixel_Sizes(face, 0, size))
    {
        log("can not set font size at " + std::to_string(size), ge::LogLevels::ERROR);
        return;
    }
    font_size = size;
}

std::map<char, ge::Glyph> &ge::Font::get_glyphs()
{
    return glyphs;
}

ge::Texture *ge::Font::get_texture()
{
    return texture;
}
