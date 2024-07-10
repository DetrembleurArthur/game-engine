#include <ge/ge.hpp>


class MyScene : public ge::Scene
{
public:
	using ge::Scene::Scene;


	ge::GameObject *go;
	ge::Text *text;

	void init() override
	{
		ge::KeyEvents::add_combo(ge::KeyCombo()
			.combine(GLFW_KEY_A)
			.on_released([this](){app.get_window().close();}));
		ge::Application::get().set_controller_update_state(false);
		
		fonts->load("./res/fonts/vintage.ttf", "vintage", 200);

		text = new ge::Text("Bonjour\nJe suis\nArthur", fonts->get("vintage"));
		text->set_color(ge::Colors::BLUE);
		text->get_transform().set_position(100, 100);

		text->create_component<ge::CallbackComponent>().set([&](float dt) {
			text->get_transform().set_position(ge::MouseInput::get_position(get_camera()));
		});

		text->get_transform().set_center_origin();
		

		add(text, ge::Layers::MAIN);

		

		

	}

	void destroy() override
	{
		
	}

	void load() override
	{
		app.resize(1400, 900);
		app.get_window().set_clear_color(ge::Colors::CYAN);

	}

	void unload() override
	{
		
	}

};


int main(int argc, char const *argv[])
{
	

	ge::Application app([]() {
		//ge::Window::hint_transparent_framebuffer(true);
	});
	app.init("Test app", 1400, 800);
	app.get_window().set_icon("./res/images/ge-logo.png");
	app.set_target_fps(0);
	
	app.get_scene_manager().create<MyScene>("arthur");
	app.get_scene_manager().set_current("arthur");

	app.run();
	return 0;
}
