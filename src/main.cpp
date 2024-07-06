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
			.on_released([](){ge::Application::get().get_window().close();}));
		ge::Application::get().set_controller_update_state(false);



		textures->load("./res/images/ge-logo.png", "logo");

		go = new ge::GameObject();
		go->get_transform().set_center_origin();
		go->as_rect(textures->get("logo"));
		go->set_color(ge::Colors::LIME);
		go->get_transform().set_size(100, 100);
		go->get_transform().set_position(300, 300);
		ge::MoveComponent& mc = go->create_component<ge::MoveComponent>();
		mc.angle_speed = 90;
		mc.angle_accel = 20;
		ge::CallbackComponent& cc = go->create_component<ge::CallbackComponent>();
		cc.set([&](float dt){
			auto mp = ge::MouseInput::get_position(get_camera());
			//mc.toward(mp, glm::vec2(100));
			//go->get_transform().set_relative_angle(mp, 45*dt, 200);
			mc.around(mp, 50);
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
		ge::Application::get().resize(1400, 900);
		ge::Application::get().get_window().set_clear_color(ge::Colors::BLACK);
		auto size = ge::Application::get().get_window().get_size();

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
