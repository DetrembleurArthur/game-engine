#include <ge/ge.hpp>
#include <chrono>
#include <ctime>

//shell:startup


class MyScene : public ge::Scene
{
public:
	using ge::Scene::Scene;

	ge::ProgressBar *pg=nullptr;

	void init() override
	{
		ge::KeyEvents::add_combo(ge::KeyCombo()
			.combine(GLFW_KEY_A)
			.on_released([this](){app.get_window().close();}));
		ge::Application::get().set_controller_update_state(false);



		fonts->load("./res/fonts/GoodBakwan.otf", "atop", 100, ge::charsets::alphanum);


		pg = new ge::ProgressBar(0, 3, 0.0, true, false);
		pg->get_root().get_transform().set_center_origin();
		pg->set_border(10, 10);
		pg->enable_text(fonts->get("atop"), renderers->get(ge::rend::text), true);
		pg->get_component<ge::TimerComponent>().create(3, -1).on_during([this](float elapsed) {
			pg->set_value(elapsed);
		});

		pg->set_position(700, 450);
		pg->set_size(50, 300);
		pg->get_root().get_component<ge::EventsComponent>().dragging(ge::DragMode::TWO_AXIS, true);

		add(pg);
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
