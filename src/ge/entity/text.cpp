#include "ge/entity/text.hpp"


ge::Text::Text(const std::string &text, ge::Font *font) : Text()
{
    this->text = text;
    this->font = font;
    as_text();
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

void ge::Text::set_text(const std::string& text)
{
    this->text = "";
    for(auto it = text.begin(); it != text.end(); it++)
    {
        if(font->get_glyphs().find(*it) != font->get_glyphs().end())
        {
            this->text += *it;
        }
    }
}

