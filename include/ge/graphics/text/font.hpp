#ifndef __GE_FONT_HPP__
#define __GE_FONT_HPP__
#include <ft2build.h>
#include <string>
#include <map>
#include <glm/glm.hpp>
#include <ge/graphics/texture.hpp>
#include FT_FREETYPE_H  

namespace ge
{
    struct Glyph
    {
        //Texture *texture;
        glm::ivec2 size;
        glm::ivec2 bearing;
        unsigned advance;
        glm::ivec2 tex_offset;
    };

    class Font
    {
    private:
        static FT_Library ft;
        FT_Face face;
        Texture *texture = nullptr;
        int font_size=0;
        std::map<char, Glyph> glyphs;
    public:
        static void init();
        static void done();
        Font(const std::string& filename, int font_size=48);
        ~Font();
        void set_font_size(int size);
        std::map<char, Glyph>& get_glyphs();
        Texture *get_texture();
    };
}

#endif

