#include <ge/ge.hpp>


class MyScene : public ge::Scene
{
public:
	using ge::Scene::Scene;

	ge::Rect *r1;
	ge::Rect *r2;

	ge::FloatNotifyProperty x_r1;


	void init() override
	{
		ge::KeyEvents::add_combo(ge::KeyCombo()
			.combine(GLFW_KEY_A)
			.on_released([this](){app.get_window().close();}));
		ge::Application::get().set_controller_update_state(false);


		r1 = new ge::Rect(100, 100);
		r1->get_transform().set_position(100, 100);
		r1->set_color(ge::Colors::LIME);
		r1->get_transform().set_center_origin();

		r2 = new ge::Rect(50, 50);
		r2->get_transform().set_position(250, 250);
		r2->set_color(ge::Colors::GOLD);
		r2->get_transform().set_center_origin();

		x_r1.on_change([this](float x){
			r2->get_transform().set_x(x);
		});

		r1->get_component<ge::CallbackComponent>().set([this](float dt) {
			r1->get_transform().set_position(get_mp());
			x_r1.set(get_mp().x);
		});

		add(r1);
		add(r2);
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
