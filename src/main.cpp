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
		srand(NULL);
		ge::KeyEvents::add_combo(ge::KeyCombo()
			.combine(GLFW_KEY_A)
			.on_released([this](){app.get_window().close();}));
		ge::Application::get().set_controller_update_state(false);

		fonts->load("./res/fonts/atop.ttf", "atop", 120);

		text = new ge::Text("Hello world !", fonts->get("atop"));
		text->get_transform().set_position(700, 450);
		text->get_transform().set_center_origin();
		text->set_color(ge::Colors::PURPLE);
		text->enable_shadow();
		text->set_shadow_color(glm::vec4(0, 0, 0, 0.5));
		text->set_shadow_offset(glm::vec2(2, 2));

		text->get_component<ge::AnimationComponent>().to_text_height(1.6, 100, 30, -1, true, ge::tweenf::ease_in_out_bounce);
		text->get_component<ge::AnimationComponent>().to_rotation(1.2, 360, 0, -1, false);
		text->get_component<ge::AnimationComponent>().to_text_offset(1.5, glm::vec2(-10, -10), glm::vec2(10, 10), -1, true);
		text->get_component<ge::AnimationComponent>().to_color(0.5, ge::Colors::GOLD, ge::Colors::PURPLE, -1, true);
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
