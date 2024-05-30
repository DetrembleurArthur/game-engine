#include <application.hpp>

int main(int argc, char const *argv[])
{
	ge::Application app([]() {
		//ge::Window::hint_maximized(true);
	});
	app.init("Test app");

	app.run();
	return 0;
}
