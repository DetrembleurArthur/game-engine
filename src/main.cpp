#include <ge/ge.hpp>
#include <chrono>
#include <ctime>

//shell:startup

class MyScene : public ge::Scene
{
public:
	using ge::Scene::Scene;

	ge::Rect *rect;

	void init() override
	{
		ge::KeyEvents::add_combo(ge::KeyCombo()
			.combine(GLFW_KEY_A)
			.on_released([this](){app.get_window().close();}));
		ge::Application::get().set_controller_update_state(false);

		rect = new ge::Rect(100, 100);
		rect->get_transform().set_position(300, 300);
		rect->set_color(ge::Colors::BLACK);
		rect->get_transform().set_center_origin();

		auto &timer = rect->get_component<ge::TimerComponent>().create(3.0, 3);
		timer.on_during([this](float elapsed){
			std::cout << elapsed << std::endl;
			rect->get_transform().set_rotation(rect->get_transform().get_rotation() + 360.0*ge::Timing::get_delta());
		}).on_ending([this, &timer](float elapsed) {
			rect->get_transform().set_size(200, 200);
			timer.abort();
		});

		add(rect);
	}

	void destroy() override
	{
		
	}

	void load() override
	{
		//app.resize(1400, 900);

	}

	void unload() override
	{
		
	}

};


int main(int argc, char const *argv[])
{
	

	ge::Application app([]() {
		
	});
	app.init("Test app", 1400, 900);
	app.get_window().set_icon("./res/images/ge-logo.png");
	app.get_window().set_clear_color(ge::Colors::CYAN);
	app.set_target_fps(0);
	
	app.get_scene_manager().create<MyScene>("arthur");
	app.get_scene_manager().set_current("arthur");

	app.run();
	return 0;
}
