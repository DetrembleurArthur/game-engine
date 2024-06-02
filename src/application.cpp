#include <application.hpp>

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
        while(!window->must_be_closed())
        {
            window->clear();
            window->swap();
            events_policy_callback();
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

ge::Application &ge::Application::get()
{
    return *ge::Application::app;
}
