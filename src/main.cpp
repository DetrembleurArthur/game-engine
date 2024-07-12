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

		ge::Node *node = new ge::Node();
		node->get_transform().set_size(1, 1);
		

		ge::Circle *circle = new ge::Circle(6, 100);
		circle->set_color(ge::Colors::LIME);
		circle->get_transform().set_position(100, 100);
		
		ge::Rect *rect = new ge::Rect(100, 50);
		rect->set_color(ge::Colors::LIME);
		rect->get_transform().set_position(500, 100);


		ge::Node *child = new ge::Node();

		ge::Circle *circle2 = new ge::Circle(3, 50);
		circle2->set_color(ge::Colors::RED);
		circle2->get_transform().set_position(100, 350);
		
		ge::Rect *rect2 = new ge::Rect(50, 100);
		rect2->set_color(ge::Colors::RED);
		rect2->get_transform().set_position(500, 300);

		child->add(circle2, true);
		child->add(rect2, true);
		

		node->add(circle, true);
		node->add(rect, true);
		node->add(child, true);

		add(node, ge::Layers::MAIN);

		circle->get_transform().set_center_origin();

		auto s = node->get_drawable_size();

		node->get_transform().set_size(s.x, s.y);
		node->get_transform().set_center_origin();

		node->create_component<ge::CallbackComponent>().set([node, this, circle](float dt) {
			node->get_transform().set_position(ge::MouseInput::get_position(camera));
			node->get_transform().set_rotation(node->get_transform().get_rotation() + 30 *dt);
			
		});
		

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
