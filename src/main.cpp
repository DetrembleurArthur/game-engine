#include <application.hpp>
#include <key_input.hpp>

int main(int argc, char const *argv[])
{
	ge::Application app([]() {
		//ge::Window::hint_transparent_framebuffer(true);
	});
	app.init("Test app");
	app.get_window().set_icon("./res/images/ge-logo.png");


	app.run();
	return 0;
}
