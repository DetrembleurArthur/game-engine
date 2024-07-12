#include <ge/ge.hpp>


class MyScene : public ge::Scene
{
public:
	using ge::Scene::Scene;

	void init() override
	{
		ge::KeyEvents::add_combo(ge::KeyCombo()
			.combine(GLFW_KEY_A)
			.on_released([this](){app.get_window().close();}));
		ge::Application::get().set_controller_update_state(false);

		ge::Rect *rect = new ge::Rect(100, 200);
		rect->get_transform().set_position(300, 300);
		rect->get_transform().set_center_origin();

		auto& cc = rect->create_component<ge::ColliderComponent>();
		cc.fit_collider(glm::vec2(0.75, 0.75), glm::vec2(0.5, 0.5));
		ge::Rect *collider = cc.create_rendered_collider();


		ge::Rect *rect2 = new ge::Rect(100, 200);
		rect2->get_transform().set_position(700, 300);
		rect2->get_transform().set_center_origin();

		auto& cc2 = rect2->create_component<ge::ColliderComponent>();
		cc2.fit_collider(glm::vec2(1, 1), glm::vec2(0.5, 0.5));
		ge::Rect *collider2 = cc2.create_rendered_collider();
		

		//cc.normalize_collider();
		rect->get_component<ge::CallbackComponent>().set([rect, this, collider, rect2](float dt) {
			auto& cc = rect->get_component<ge::ColliderComponent>();
			//rect->get_transform().set_position(ge::MouseInput::get_position(get_camera()));
			rect->get_transform().set_rotation(rect->get_transform().get_rotation() + 20 * dt);
			cc.update_rendered_collider(collider);
			if(cc.contains(rect2->get_component<ge::ColliderComponent>()))
			{
				collider->set_color(ge::Color(0, 1, 0, 0.5));
			}
			else
			{
				collider->set_color(ge::Color(1, 0, 0, 0.5));
			}
		});

		rect2->get_component<ge::CallbackComponent>().set([rect2, this, collider2](float dt) {
			auto& cc2 = rect2->get_component<ge::ColliderComponent>();
			rect2->get_transform().set_position(ge::MouseInput::get_position(get_camera()));
			//rect2->get_transform().set_rotation(rect2->get_transform().get_rotation() + 20 * dt);
			cc2.update_rendered_collider(collider2);
		});


		

		add(rect, ge::Layers::MAIN);
		add(collider, ge::Layers::MAIN);

		add(rect2, ge::Layers::MAIN);
		add(collider2, ge::Layers::MAIN);

		

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
