#include "ge/graphics/text/font.hpp"
#include <ge/utils/log.hpp>


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
    if(FT_New_Face(Font::ft, filename.c_str(), 0, &face))
    {
        log("font '" + filename + "' can not be loaded", ge::LogLevels::ERROR);
        return;
    }
    set_font_size(font_size);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for(unsigned char c = 0; c < 128; c++)
    {
        if(FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            log("can not load '" + std::to_string(c) + "' char in font " + filename, LogLevels::WARNING);
            continue;
        }
        Glyph glyph = {
            .texture=new Texture(face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer),
            .size=glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            .bearing=glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            .advance=static_cast<unsigned>(face->glyph->advance.x)
        };
        glyphs.insert(std::pair<char, Glyph>(c, glyph));
    }
    log("font '" + filename + "' loaded", ge::LogLevels::FONT);
}

ge::Font::~Font()
{
    for(auto it = glyphs.begin(); it != glyphs.end(); it++)
    {
        Texture *tex = it->second.texture;
        if(tex)
        {
            delete tex;
            tex = nullptr;
        }
    }
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
