#include <ge.hpp>


class MyScene : public ge::Scene
{
public:
	using ge::Scene::Scene;

	ge::Mesh *vbuffer;
	ge::Transform tr;
	int points = 3;

	void init() override
	{
		ge::KeyEvents::add_combo(ge::KeyCombo()
			.combine(GLFW_KEY_A)
			.on_released([](){ge::Application::get().get_window().close();}));
		ge::Application::get().set_controller_update_state(false);


		vbuffer = ge::Mesh::create_rect(true);

		vbuffer->set_color(ge::Colors::LIME);
		tr.set_size(50, 50);
		tr.set_position(0, ge::Application::get().get_window().get_size().y/2);


		textures->load("./res/images/ge-logo.png", "logo");

	}

	void destroy() override
	{
		delete vbuffer;
	}

	void load() override
	{
		//ge::Application::get().get_window().set_clear_color(ge::Colors::GRAY);
		ge::Application::get().resize(1400, 900);
		ge::Application::get().get_window().set_clear_color(ge::Colors::SILVER);

		

	}

	void unload() override
	{
		
	}

	void update(double dt) override
	{
		
		tr.set_position(ge::MouseInput::get_position(*camera).x, ge::MouseInput::get_position(*camera).y);

		
	}

	void draw(double dt) override
	{
		renderer->begin();
		renderer->draw(dt, *vbuffer, tr, textures->get("logo"));
		renderer->end();
	}
};


int main(int argc, char const *argv[])
{
	ge::Application app([]() {
		//ge::Window::hint_transparent_framebuffer(true);
	});
	app.init("Test app", 1400, 800);
	app.get_window().set_icon("./res/images/ge-logo.png");
	app.set_target_fps(120);
	
	app.get_scene_manager().create<MyScene>("arthur");
	app.get_scene_manager().set_current("arthur");

	app.run();
	return 0;
}
