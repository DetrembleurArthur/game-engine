#include <application.hpp>
#include <global_events.hpp>
#include <key_input.hpp>
#include <mouse_input.hpp>
#include <controller_events.hpp>
#include <controller_input.hpp>
#include <timing.hpp>
#include <thread>
#include <colors.hpp>
#include <window_events.hpp>
#include <mouse_events.hpp>
#include <key_events.hpp>


ge::Application *ge::Application::app=nullptr;

void ge::Application::loop()
{
    float dt = Timing::get_delta();
    window->clear();
    Scene *current_scene = scene_manager.get_current();
    if(current_scene)
    {
        if(enable_controller_update)
            ControllerInput::update_controllers();
        current_scene->update(dt);
        current_scene->draw(dt);
    }
    window->swap();
    events_policy_callback();
    loop_times.second = Timing::get_sec();
    dt = loop_times.second - loop_times.first;
    if(target_fps > 0 && dt < 1.0 / target_fps)
    {
        std::this_thread::sleep_for(std::chrono::duration<double>(1.0 / target_fps - dt));
        loop_times.second += 1.0 / target_fps - dt;
        dt = loop_times.second - loop_times.first;
    }
    Timing::set_delta(dt);
    loop_times.first = loop_times.second;
}

ge::Application::Application(void (*hint_callback)()) : hint_callback(hint_callback)
{
    if(ge::Application::app)
    {
        log("only one application can run at a time", ge::LogLevels::ERROR);
        exit(EXIT_FAILURE);
    }
    ge::Application::app = this;
}

ge::Application::~Application()
{
    scene_manager.delete_scenes();
    MouseInput::destroy_cursor();
    Shader::unload_default_shaders();
    if(window)
    {
        delete window;
    }
    glfwTerminate();
    log("application terminated");
}

void ge::Application::init(const std::string& title, unsigned width, unsigned height)
{
    log("initializing");
    log("GLFW version: " + std::string(glfwGetVersionString()));
    initialized = glfwInit();
    if(initialized)
    {
        GlobalEvents::init();
        GlobalEvents::error_callback([](int err, const char *desc) {
            log(std::string(desc) + " (" + std::to_string(err) + ")", LogLevels::GLFW_ERROR);
        });
        log("glfw initialization success");
        log("current monitor is '" + ge::Monitor::get_primary_monitor().get_name() + "'");
        log("hints configuration");
        hint_callback();
        window = new Window(title, width, height);
        WindowEvents::init(window->get_pointer());
        KeyEvents::init(window->get_pointer());
        MouseEvents::init(window->get_pointer());
        window->set_clear_color(ge::Colors::BLACK);
        KeyInput::set_window(window->get_pointer());
        MouseInput::set_window(window->get_pointer());
        ControllerEvents::init();
        window->make_current();
        viewport = glm::vec4(0, 0, window->get_size().x, window->get_size().y);
        WindowEvents::on_window_frame_buffer_size_changed([this](const glm::vec2& size){
            int aspect_width = size.x;
            int aspect_height = aspect_width / get_window().get_aspect_ratio();
            if(aspect_height > size.y)
            {
                aspect_height = size.y;
                aspect_width = aspect_height * get_window().get_aspect_ratio();
            }
            int vpx = size.x / 2 - aspect_width / 2.0;
            int vpy = size.y / 2 - aspect_height / 2.0;
            glViewport(vpx, vpy, aspect_width, aspect_height);
            viewport = glm::vec4(vpx, vpy, aspect_width, aspect_height);
            loop();
        });
    }
    else
    {
        log("glfw initialization failed", LogLevels::ERROR);
    }
    glewExperimental = GL_TRUE;
    auto code = glewInit();
    if(code == GLEW_OK)
    {
        log("glew initialization success");
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_LINE_SMOOTH);
        Shader::load_default_shaders();
    }
    else
    {
        log("glew initialization failed", LogLevels::ERROR);
        fprintf(stderr, "Error: %s\n", glewGetErrorString(code));
    }
}


void ge::Application::run()
{
    if(is_initialized() && window->is_created())
    {
        log("running");
        if(target_fps > 0)
        {
            Timing::set_delta(1.0/target_fps);
        }
        loop_times.first = Timing::get_sec();
        loop_times.second = 0.0;
        while(!window->must_be_closed())
        {
            loop();
        }
    }
    else
    {
        log("unabled to run due to failed initilization", LogLevels::ERROR);
    }
}

bool ge::Application::is_initialized() const
{
    return initialized;
}

void ge::Application::poll_events_policy()
{
    events_policy_callback = glfwPollEvents;
}

void ge::Application::wait_events_policy()
{
    events_policy_callback = glfwWaitEvents;
}

void ge::Application::post_empty_event()
{
    glfwPostEmptyEvent();
}

ge::Window &ge::Application::get_window()
{
    return *window;
}

ge::SceneManager &ge::Application::get_scene_manager()
{
    return scene_manager;
}

void ge::Application::set_target_fps(int fps)
{
    this->target_fps = fps;
}


int ge::Application::get_fps()
{
    return 1.0/ge::Timing::get_delta();
}

void ge::Application::set_controller_update_state(bool value)
{
    enable_controller_update = value;
}

glm::vec4 ge::Application::get_viewport()
{
    return viewport;
}

ge::Application &ge::Application::get()
{
    return *ge::Application::app;
}

void ge::Application::adapt_viewport()
{
    glViewport(0, 0, window->get_size().x, window->get_size().y);
    viewport = glm::vec4(0, 0, window->get_size().x, window->get_size().y);
    window->reset_vp_aspect_ratio();
    get_scene_manager().get_current()->get_camera()->update_ortho();
}

void ge::Application::resize(float width, float height)
{
    auto&& size = window->get_size();
    width = width > 0 ? width : size.x;
    height = height > 0 ? height : size.y;
    window->set_size(glm::uvec2(width, height));
    adapt_viewport();
}
