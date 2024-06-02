#include <application.hpp>
#include <key_input.hpp>


//NOW https://www.glfw.org/docs/latest/input_guide.html (time input)
int main(int argc, char const *argv[])
{
	ge::Application app([]() {
		//ge::Window::hint_transparent_framebuffer(true);
	});
	app.init("Test app");
	app.get_window().set_icon("./res/images/ge-logo.png");

	ge::Controller *controller=&ge::ControllerInput::get();
	ge::ControllerEvents::on_joystick_connected([&controller](int jid) {
		controller = &ge::ControllerInput::get(jid);
	});
	ge::KeyCombo kc;
	kc.combine(GLFW_KEY_SPACE);
	kc.on_pressed([&controller](){
		controller->update_gamepad();
		std::cout << "> " << (unsigned int)controller->gamepad_buttons.start << std::endl;
		std::cout << "> " << controller->gamepad_axes.left_trigger << std::endl;
	});
	ge::KeyEvents::add_combo(kc);




	app.run();
	return 0;
}
