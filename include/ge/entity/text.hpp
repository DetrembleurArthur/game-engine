#ifndef __GE_TEXT_HPP__
#define __GE_TEXT_HPP__
#include <ge/entity/game_object.hpp>
#include <ge/graphics/text/font.hpp>

namespace ge
{
    enum TextAlign
    {
        LEFT,
        RIGHT,
        CENTER
    };

    class Text : public GameObject
    {
    private:
        ge::Font *font=nullptr;
        std::string text;
        int sticky_index = -1;
        int line_space=0;
        TextAlign align = TextAlign::LEFT;
        bool shadow_enabled=false;
        glm::vec2 shadow_offset;
        Color shadow_color;
    public:
        using GameObject::GameObject;
        Text(const std::string& text, ge::Font *font, int line_space=0);
        virtual ~Text();
        ge::Font *get_font();
        void set_font(ge::Font *font);
        std::string get_text();
        void set_text(std::string text);
        void set_text_width(float width);
        void set_text_height(float height);
        void set_text_align(ge::TextAlign align);
        void set_dynamic_text_size();
        void enable_shadow(bool value=true);
        void set_shadow_offset(glm::vec2 offset);
        void set_shadow_color(Color color);
        bool is_shadow_enabled() const;
        glm::vec2 get_shadow_offset() const;
        Color get_shadow_color() const;
    };
}

#endif
