#ifndef __GE_BUTTON_HPP__
#define __GE_BUTTON_HPP__
#include <ge/entity/node.hpp>
#include <ge/entity/rect.hpp>
#include <ge/entity/text.hpp>
#include <ge/graphics/renderer.hpp>
#include <functional>

namespace ge
{
    class Button : public Node
    {
    private:
        Rect *background=nullptr;
        Text *text=nullptr;
        ge::Color hover_color=ge::Colors::NAVY;
        ge::Color click_color=ge::Colors::WHITE;
        ge::Color idle_color=ge::Colors::BLACK;
        std::function<void(ge::Button&)> callback = [](ge::Button& btn){};
    public:
        Button(int width, int height, bool tex=false, bool dynamic=false);
        Rect& get_background();
        Text& get_text();
        void set_text(const std::string& text, ge::Font *font=nullptr, ge::Renderer *text_renderer=nullptr);
        void on_click(std::function<void(ge::Button&)> callback);
        void set_hover_color(ge::Color color);
        void set_click_color(ge::Color color);
        void set_idle_color(ge::Color color);
        void set_position(float x, float y);
        void set_size(float width, float height);
    };
}

#endif
