#include "ge/entity/text.hpp"
#include <ge/utils/utils.hpp>


ge::Text::Text(const std::string &text, ge::Font *font, int line_space) : Text()
{
    this->font = font;
    this->texture = font->get_texture();
    this->line_space = line_space;
    set_text(text);
}

ge::Text::~Text()
{
    
}

void ge::Text::set_font(ge::Font *font)
{
    this->font = font;
}

ge::Font *ge::Text::get_font()
{
    return font;
}

std::string ge::Text::get_text()
{
    return text;
}

void ge::Text::set_text(std::string text)
{
    this->text = text;
    if(text.find('\n') != std::string::npos)
        ge::utils::reverse_words(text);
    float *vertices = new float[text.length() * 5 * 4]; // 5 données pour 4 vertex
    unsigned *elements = new unsigned[text.length() * 6]; // 6 indexs par characters
    if(this->mesh)
    {
        delete this->mesh;
        this->mesh = nullptr;
    }

    glm::uvec2 tex_size = font->get_texture()->get_size();
    int i = 0, j = 0;
    glm::ivec2 offsets(0, 0);
    glm::vec2 max_text_size(0, 0);
    float min_xpos = -1;
    float max_xpos = 0;
    float min_ypos = 10e100;
    float max_ypos = -10e100;
    float line_height_min = 10e100;
    float line_height_max = -10e100;
    std::vector<std::pair<int, float>> lines_widths;
    float width = -10e100;
    for(auto it = text.begin(); it != text.end(); it++)
    {
        if(*it == '\n')
        {
            offsets.y -= line_height_max - line_height_min + line_space;
            line_height_min = 10e100;
            line_height_max = -10e100;
            offsets.x = 0;
            lines_widths.push_back(std::pair<int, float>(i, width));
            width = -10e100;
        }
        else if(font->get_glyphs().find(*it) != font->get_glyphs().end())
        {
            Glyph& glyph = font->get_glyphs()[*it];
            float posx = offsets.x + glyph.bearing.x;
            float posy = offsets.y - glyph.bearing.y;
            min_xpos = std::min(min_xpos, posx);
            max_xpos = std::max(max_xpos, posx + glyph.size.x);
            min_ypos = std::min(min_ypos, posy);
            max_ypos = std::max(max_ypos, posy + glyph.size.y);
            line_height_min = std::min(line_height_min, posy);
            line_height_max = std::max(line_height_max, posy + glyph.size.y);
            width = std::max(width, posx + glyph.size.x);
            vertices[i++] = posx;
            vertices[i++] = posy;
            vertices[i++] = 0;
            vertices[i++] = glyph.tex_offset.x / (float)tex_size.x;
            vertices[i++] = glyph.tex_offset.y / (float)tex_size.y;

            vertices[i++] = posx;
            vertices[i++] = posy + glyph.size.y;
            vertices[i++] = 0;
            vertices[i++] = glyph.tex_offset.x / (float)tex_size.x;
            vertices[i++] = glyph.tex_offset.y / (float)tex_size.y + glyph.size.y / (float)tex_size.y;

            vertices[i++] = posx + glyph.size.x;
            vertices[i++] = posy + glyph.size.y;
            vertices[i++] = 0;
            vertices[i++] = glyph.tex_offset.x / (float)tex_size.x + glyph.size.x / (float)tex_size.x;
            vertices[i++] = glyph.tex_offset.y / (float)tex_size.y + glyph.size.y / (float)tex_size.y;

            vertices[i++] = posx + glyph.size.x;
            vertices[i++] = posy;
            vertices[i++] = 0;
            vertices[i++] = glyph.tex_offset.x / (float)tex_size.x + glyph.size.x / (float)tex_size.x;
            vertices[i++] = glyph.tex_offset.y / (float)tex_size.y;

            elements[j * 6] = j * 4;
            elements[j * 6+1] = j * 4 + 1;
            elements[j * 6+2] = j * 4 + 2;
            elements[j * 6+3] = j * 4;
            elements[j * 6+4] = j * 4 + 2;
            elements[j * 6+5] = j * 4 + 3;
            j++;

            offsets.x += (glyph.advance >> 6);
        }
    }
    lines_widths.push_back(std::pair<int, float>(i, width));
    max_text_size.x = max_xpos - min_xpos;
    max_text_size.y = max_ypos - min_ypos;
    for(int i = 0; i < text.length() * 5 * 4; i += 5)
    {
        // normalisation
        vertices[i] /= max_text_size.x;
        //vertices[i+1] += max_text_size.y;
        vertices[i+1] /= max_text_size.y;
        vertices[i+1] += 1;
    }
    if(align != TextAlign::LEFT)
    {
        int line_i = 0;
        for(auto& pair : lines_widths)
        {
            float line_width = (pair.second - min_xpos) / max_text_size.x;
            float padding_width = 1 - line_width;
            float padding = 0;
            int line_index = pair.first;
            while(line_i < line_index)
            {
                switch(align)
                {
                    case TextAlign::RIGHT:
                        padding = padding_width;
                        break;
                    case TextAlign::CENTER:
                        padding = padding_width / 2.0;
                        break;
                }
                vertices[line_i] += padding;
                line_i += 5;
            }
        }
    }
    
    glm::vec2&& old_size = transform.get_size();
    transform.set_size(max_text_size.x, max_text_size.y);
    if(sticky_index == 0)
        set_text_width(old_size.x);
    else if(sticky_index == 1)
        set_text_height(old_size.y);

    MeshAttribute ma = {
        .layers_ref=MeshLayer::DEFAULT_LAYERS,
        .layers=2,
        .vertices=vertices,
        .vertices_bytes=text.length() * 5 * 4 * sizeof(float)
    };
    this->mesh = new Mesh();
    this->mesh->set_dynamic(false);
    this->mesh->fill(&ma, text.length() * 6 * sizeof(unsigned), elements, true);
    delete[] vertices;
    delete[] elements;
}

void ge::Text::set_text_width(float width)
{
    glm::vec2&& size = transform.get_size();
    transform.set_size(width, width * (size.y / size.x));
    sticky_index = 0;
}

void ge::Text::set_text_height(float height)
{
    glm::vec2&& size = transform.get_size();
    transform.set_size(height * (size.x / size.y), height);
    sticky_index = 1;
}

void ge::Text::set_text_align(ge::TextAlign align)
{
    this->align = align;
    set_text(text);
}

void ge::Text::set_dynamic_text_size()
{
    sticky_index = -1;
}

void ge::Text::enable_shadow(bool value)
{
    shadow_enabled = value;
}

void ge::Text::set_shadow_offset(glm::vec2 offset)
{
    shadow_offset = offset;
}

void ge::Text::set_shadow_color(Color color)
{
    shadow_color = color;
}

bool ge::Text::is_shadow_enabled() const
{
    return shadow_enabled;
}

glm::vec2 ge::Text::get_shadow_offset() const
{
    return shadow_offset;
}

ge::Color& ge::Text::get_shadow_color()
{
    return shadow_color;
}
