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
    }
    else
    {
        log("initialization failed", LogLevels::ERROR);
    }
}

void ge::Application::run()
{
    if(is_initialized() && window->is_created())
    {
        log("running");
        while(!window->must_be_closed())
        {
            window->clear();
            window->swap();
            window->poll_events();
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

ge::Window &ge::Application::get_window()
{
    return *window;
}

ge::Application &ge::Application::get()
{
    return *ge::Application::app;
}
