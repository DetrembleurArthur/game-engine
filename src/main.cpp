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
		
		fonts->load("./res/fonts/elden.otf", "elden", 50);

		text = new ge::Text("Bonjour les gars\nJe suis Arthur !", fonts->get("elden"), 20);
		text->set_color(ge::Colors::BLACK);
		text->get_transform().set_position(100, 100);
		text->set_text_align(ge::TextAlign::CENTER);
		text->set_shadow_color(ge::Color(0, 0, 0, 0.25));
		text->set_shadow_offset(glm::vec2(2, 2));
		text->enable_shadow();

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
