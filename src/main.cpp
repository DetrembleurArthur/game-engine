#include <ge.hpp>


class MyScene : public ge::Scene
{
public:
	using ge::Scene::Scene;

	ge::Mesh vbuffer;
	ge::Transform tr;

	void init() override
	{
		ge::KeyEvents::add_combo(ge::KeyCombo()
			.combine(GLFW_KEY_A)
			.on_released([](){ge::Application::get().get_window().close();}));
		ge::Application::get().set_controller_update_state(false);
		//ge::Application::get().get_window().set_aspect_ratio(16, 9);
		ge::Application::get().get_window().set_size(glm::uvec2(1400, 800));


		float vertices[] = {
			0.0f, 0.0f, 0.0f,
			0.0f,  1, 0.0f,
			1, 1, 0.0f,
			1,  0, 0.0f
		};
		
		unsigned elements[] = {
			0, 1, 2,
			0, 2, 3
		};
		vbuffer.fill(sizeof(vertices), vertices, sizeof(elements), elements);

		vbuffer.set_color(ge::Colors::BLUE);
		tr.set_size(100, 150);

		tr.set_tl_origin();
		tr.set_position(0, 0);
		std::cout << tr.get_width() << " " << tr.get_height() << std::endl;
	}

	void destroy() override
	{
		
	}

	void load() override
	{
		//ge::Application::get().get_window().set_clear_color(ge::Colors::GRAY);
		

	}

	void unload() override
	{
		
	}

	void update(double dt) override
	{
		tr.set_center_position(ge::MouseInput::get_position(*camera));
		//camera->get_position().x += 100 * dt;
		//tr.set_rotation(tr.get_rotation() + 10 * dt);
		
	}

	void draw(double dt) override
	{
		renderer->begin();
		renderer->draw(dt, vbuffer, tr);
		renderer->end();
	}
};


int main(int argc, char const *argv[])
{
	ge::Application app([]() {
		//ge::Window::hint_transparent_framebuffer(true);
	});
	app.init("Test app");
	app.get_window().set_icon("./res/images/ge-logo.png");
	app.set_target_fps(60);
	
	app.get_scene_manager().create<MyScene>("arthur");
	app.get_scene_manager().set_current("arthur");

	app.run();
	return 0;
}
