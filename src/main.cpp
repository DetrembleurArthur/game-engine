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

		text = new ge::Text("Magic Vintage Demo", fonts->get("vintage"));
		text->set_color(ge::Colors::BLUE);
		text->get_transform().set_position(100, 300);
		

		add(text, ge::Layers::MAIN);

		ge::KeyEvents::on_character([&](auto c) {
			if(c == ":") text->set_text("");
			else
			text->set_text(text->get_text() + c);
		});

		

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
