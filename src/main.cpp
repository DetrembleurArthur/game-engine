#include <ge/ge.hpp>


class MyScene : public ge::Scene
{
public:
	using ge::Scene::Scene;


	ge::Circle *go;
	ge::Rect *rect;
	ge::Text *text;

	void init() override
	{
		ge::KeyEvents::add_combo(ge::KeyCombo()
			.combine(GLFW_KEY_A)
			.on_released([this](){app.get_window().close();}));
		ge::Application::get().set_controller_update_state(false);

		textures->load("./res/images/ge-logo.png", "logo");

		go = new ge::Circle(30, textures->get("logo"));
		go->set_radius(100);
		go->set_points(3);
		go->get_transform().set_position(100, 100);
		go->set_color(ge::Colors::RED);
		go->get_transform().set_br_origin();
		go->create_component<ge::CallbackComponent>().set([&](float dt) {
			go->get_transform().set_position(ge::MouseInput::get_position(get_camera()));
			std::cout << go->get_color().x << ", " << go->get_color().y << ", " << go->get_color().z << ", " << go->get_color().w << std::endl;
		});
		
		fonts->load("./res/fonts/elden.otf", "elden", 50);

		text = new ge::Text("Elden Ring", fonts->get("elden"), 20);
		text->set_color(ge::Colors::BLACK);
		auto&& size = app.get_window().get_size();
		text->get_transform().set_position(size.x/2, size.y/2);
		text->set_text_align(ge::TextAlign::CENTER);
		text->set_shadow_color(ge::Color(0, 0, 0, 0.25));
		text->set_shadow_offset(glm::vec2(2, 2));
		text->enable_shadow();

		

		go->create_component<ge::CallbackComponent>().set([&](float dt) {
			go->get_transform().set_position(ge::MouseInput::get_position(get_camera()));
		});
		//go->get_transform().set_center_origin();

		text->get_transform().set_center_origin();
		

		add(text, ge::Layers::MAIN);
		add(go, ge::Layers::MAIN);
		

		

		

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
