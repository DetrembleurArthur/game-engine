#include <ge.hpp>

/*

dist = sqrt(2x^2)

*/
class MyScene : public ge::Scene
{
public:
	using ge::Scene::Scene;


	ge::GameObject *go;
	ge::GameObject *bg;

	void init() override
	{
		ge::KeyEvents::add_combo(ge::KeyCombo()
			.combine(GLFW_KEY_A)
			.on_released([this](){app.get_window().close();}));
		ge::Application::get().set_controller_update_state(false);



		textures->load("./res/images/ge-logo.png", "logo");

		go = new ge::GameObject();
		go->get_transform().set_center_origin();
		go->as_rect(textures->get("logo"));
		go->set_color(ge::Colors::LIME);
		ge::Transform& tr = *go;
		tr.set_size(100, 100);

		auto&& size = app.get_window().get_size();
		tr.set_position(size.x/2, size.y/2);


		auto& ec = go->create_component<ge::EventsComponent>();
		ec.on_mouse_hover([this](auto *event) {
			get_camera()->get_position().x += 10;
			bg->get_transform().set_position(get_camera()->get_position());
		});

		bg = new ge::GameObject();
		
		bg->get_transform().set_tl_position(glm::vec2(0, 0));
		bg->set_color(ge::Colors::SILVER);

		add(bg, ge::Layers::BG);
		add(go, ge::Layers::MAIN);


		

	}

	void destroy() override
	{
		
	}

	void load() override
	{
		//ge::Application::get().get_window().set_clear_color(ge::Colors::GRAY);
		app.resize(1400, 900);
		app.get_window().set_clear_color(ge::Colors::BLACK);
		auto size = app.get_window().get_size();

		bg->as_rect(size.x, size.y);


		

		

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
