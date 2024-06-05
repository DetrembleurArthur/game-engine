#include <ge.hpp>


class MyScene : public ge::Scene
{
public:
	using ge::Scene::Scene;

	void init() override
	{
		ge::KeyEvents::add_combo(ge::KeyCombo()
			.combine(GLFW_KEY_A)
			.on_released([](){ge::Application::get().get_window().close();}));
		ge::Application::get().set_controller_update_state(false);
	}

	void destroy() override
	{
		
	}

	void load() override
	{

	}

	void unload() override
	{

	}

	void update(double dt) override
	{
		
	}

	void draw(double dt) override
	{

	}
};


int main(int argc, char const *argv[])
{
	ge::Application app([]() {
		//ge::Window::hint_transparent_framebuffer(true);
	});
	app.init("Test app");
	app.get_window().set_icon("./res/images/ge-logo.png");
	app.set_target_fps(60);
	app.get_scene_manager().create<MyScene>("arthur");
	app.get_scene_manager().set_current("arthur");

	/*
	ge::Clipboard::set("Hello world !");
	ge::Clipboard::get();

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

	ge::KeyCombo kc2;
	kc2.combine(GLFW_KEY_ENTER).combine(GLFW_KEY_RIGHT_SHIFT);
	kc2.on_pressed([](){ std::cout << "pressed" << std::endl;});
	kc2.on_released([](){ std::cout << "released" << std::endl;});
	ge::KeyEvents::add_combo(kc2);
	*/




	app.run();
	return 0;
}
