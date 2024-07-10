#ifndef __GE_TEXT_HPP__
#define __GE_TEXT_HPP__
#include <ge/entity/game_object.hpp>
#include <ge/graphics/text/font.hpp>

namespace ge
{
    class Text : public GameObject
    {
    private:
        ge::Font *font=nullptr;
        std::string text;
        int sticky_index = -1;
    public:
        using GameObject::GameObject;
        Text(const std::string& text, ge::Font *font);
        virtual ~Text();
        ge::Font *get_font();
        void set_font(ge::Font *font);
        std::string get_text();
        void set_text(std::string text);
        void set_text_width(float width);
        void set_text_height(float height);
        void set_dynamic_text_size();
    };
}

#endif
