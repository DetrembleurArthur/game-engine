#include <ge/ge.hpp>
#include <chrono>
#include <ctime>

//shell:startup


class MyScene : public ge::Scene
{
public:
	using ge::Scene::Scene;

	ge::Text *text;
	ge::Rect *collider;

	void init() override
	{
		ge::KeyEvents::add_combo(ge::KeyCombo()
			.combine(GLFW_KEY_A)
			.on_released([this](){app.get_window().close();}));
		ge::Application::get().set_controller_update_state(false);

		fonts->load("./res/fonts/atop.ttf", "atop", 100);

		text = new ge::Text("Hello world !", fonts->get("atop"));
		text->get_transform().set_position(700, 450);
		text->get_transform().set_center_origin();
		text->set_color(ge::Colors::PURPLE);
		text->enable_shadow();
		text->set_shadow_color(glm::vec4(0, 0, 0, 0.5));
		text->set_shadow_offset(glm::vec2(2, 2));


		collider = new ge::Rect();
		collider->set_color(ge::Color(1, 0, 0, 0.4));

		text->get_component<ge::ColliderComponent>().fit_collider(glm::vec2(1, 1));

		text->get_component<ge::CallbackComponent>().set([this](float dt) {
			text->get_component<ge::ColliderComponent>().update_rendered_collider(&collider->get_transform());
			if(text->get_component<ge::ColliderComponent>().contains(get_mp()))
				text->set_color(ge::Colors::GREEN);
			else
				text->set_color(ge::Colors::RED);
		});

		text->get_component<ge::EventsComponent>().dragging();
		text->get_component<ge::AnimationComponent>().to_rotation(5, 360, 0, -1, true, ge::tweenf::ease_in_out_quad);

		add(text);
		add(collider);
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
