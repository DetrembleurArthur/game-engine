#include <application.hpp>
#include <global_events.hpp>
#include <key_input.hpp>
#include <mouse_input.hpp>
#include <controller_events.hpp>
#include <timing.hpp>
#include <thread>

ge::Application *ge::Application::app=nullptr;

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
        log("initialization success");
        log("current monitor is '" + ge::Monitor::get_primary_monitor().get_name() + "'");
        log("hints configuration");
        hint_callback();
        window = new Window(title, width, height);
        KeyInput::set_window(window->get_pointer());
        MouseInput::set_window(window->get_pointer());
        ControllerEvents::init();
    }
    else
    {
        log("initialization failed", LogLevels::ERROR);
    }
}

void ge::Application::run()
{
    window->make_current();
    if(is_initialized() && window->is_created())
    {
        log("running");
        double dt = 1.0/(target_fps == 0 ? 60 : target_fps);
        double t0 = Timing::get_sec();
        double t1 = 0.0;
        while(!window->must_be_closed())
        {
            window->clear();

            Scene *current_scene = scene_manager.get_current();
            if(current_scene)
            {
                current_scene->update(dt);
                current_scene->draw(dt);
            }

            window->swap();
            events_policy_callback();
            t1 = Timing::get_sec();
            dt = t1 - t0;
            if(dt < 1.0 / target_fps)
            {
                std::this_thread::sleep_for(std::chrono::duration<double>(1.0 / target_fps - dt));
                t1 += 1.0 / target_fps - dt;
                dt = t1 - t0;
                Timing::set_delta(dt);
            }
            t0 = t1;
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

ge::Application &ge::Application::get()
{
    return *ge::Application::app;
}
