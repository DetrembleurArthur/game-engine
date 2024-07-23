#include <ge/ge.hpp>
#include <chrono>
#include <ctime>

//shell:startup


class MyScene : public ge::Scene
{
public:
	using ge::Scene::Scene;

	ge::Text *text;

	void init() override
	{
		ge::KeyEvents::add_combo(ge::KeyCombo()
			.combine(GLFW_KEY_A)
			.on_released([this](){app.get_window().close();}));
		ge::Application::get().set_controller_update_state(false);

		fonts->load("./res/fonts/atop.ttf", "atop", 100, ge::charsets::numeric);
		text = new ge::Text("0", fonts->get("atop"));
		text->get_component<ge::RendererComponent>().set_renderer(renderers->get(ge::rend::text));
		text->get_transform().set_position(700, 450);
		text->get_transform().set_center_origin();
		text->set_color(ge::Colors::BLACK);
		text->set_max_char(5);
		text->get_component<ge::TimerComponent>().create(1, ge::Timer::INF).on_ending([this](float elapsed) {
			text->set_text(text->get_text() + "0");
		});

		text->set_text_height(50);

		


		add(text);
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
