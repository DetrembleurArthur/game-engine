#ifndef __GE_APPLICATION_HPP__
#define __GE_APPLICATION_HPP__
#include <iostream>
#include <ge/core/window.hpp>
#include <ge/core/scene_manager.hpp>
#include <ge/audio/audio.hpp>


namespace ge
{
    class Application
    {
    private:
        static Application *app;
        bool initialized=false;
        ge::Window *window=nullptr;
        int target_fps=30;
        void (*events_policy_callback)()=glfwPollEvents;
        void (*hint_callback)();
        SceneManager scene_manager;
        bool enable_controller_update=false;
        glm::vec4 viewport;
        std::pair<float, float> loop_times;
        void loop();
    public:
        Application(void (*hint_callback)()=[](){ge::log("default hints");});
        ~Application();
        void init(const std::string& title="Untitled", unsigned width=640, unsigned height=480);
        void run();
        bool is_initialized() const;
        void poll_events_policy();
        void wait_events_policy();
        void post_empty_event();
        ge::Window& get_window();
        ge::SceneManager& get_scene_manager();
        void set_target_fps(int fps=30);
        int get_fps();
        void set_controller_update_state(bool value=true);
        glm::vec4 get_viewport();
        static Application& get();
        void adapt_viewport();
        void resize(float width=-1, float height=-1);
    };
}

#endif
