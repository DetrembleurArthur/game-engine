#ifndef __GE_WINDOW_HPP__
#define __GE_WINDOW_HPP__
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <monitor.hpp>
#include <window_events.hpp>
#include <log.hpp>

namespace ge
{
    class Window
    {
    private:
        GLFWwindow *window=nullptr;
    public:
        Window(const std::string& title="Untitled", unsigned width=640, unsigned height=480);
        ~Window();
        void make_current();
        bool must_be_closed() const;
        void clear();
        void swap();
        void poll_events();
        bool is_created() const;
        void close();
        void set_monitor(Monitor& monitor);
        void set_size(glm::uvec2 size);
        void set_limits(int min_width=GLFW_DONT_CARE, int min_height=GLFW_DONT_CARE, int max_width=GLFW_DONT_CARE, int max_height=GLFW_DONT_CARE);
        void set_aspect_ratio(int num=GLFW_DONT_CARE, int den=GLFW_DONT_CARE);
        void set_position(glm::vec2 position);
        void set_title(const std::string& title);
        glm::uvec2 get_size();
        glm::ivec4 get_frame_size();
        glm::uvec2 get_frame_buffer_size();
        glm::vec2 get_content_scale();
        glm::vec2 get_position();
        GLFWwindow *get_pointer();
        std::string get_title();
        void set_icon(const std::string& icon_path="");
        static void hint_resizable(bool value=true);
        static void hint_visible(bool value=true);
        static void hint_decorated(bool value=true);
        static void hint_focused(bool value=true);
        static void hint_auto_iconify(bool value=true);
        static void hint_floating(bool value=true);
        static void hint_maximized(bool value=true);
        static void hint_center_cursor(bool value=true);
        static void hint_transparent_framebuffer(bool value=true);
        static void hint_focus_on_show(bool value=true);
        static void hint_xposition(int x);
        static void hint_yposition(int y);
    };
}


#endif
