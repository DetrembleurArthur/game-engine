#include <ge.hpp>


class MyScene : public ge::Scene
{
public:
	using ge::Scene::Scene;

	ge::Mesh *vbuffer;
	ge::Transform tr;

	void init() override
	{
		ge::KeyEvents::add_combo(ge::KeyCombo()
			.combine(GLFW_KEY_A)
			.on_released([](){ge::Application::get().get_window().close();}));
		ge::Application::get().set_controller_update_state(false);
		//ge::Application::get().get_window().set_aspect_ratio(16, 9);


		vbuffer = ge::Mesh::create_rect();

		vbuffer->set_color(ge::Colors::BLUE);
		tr.set_size(100, 100);

		//tr.set_tl_origin();
		tr.set_position(50, 50);
	}

	void destroy() override
	{
		delete vbuffer;
	}

	void load() override
	{
		//ge::Application::get().get_window().set_clear_color(ge::Colors::GRAY);

		ge::Application::get().resize(1000, 800);
		

	}

	void unload() override
	{
		
	}

	void update(double dt) override
	{
		tr.set_center_position(ge::MouseInput::get_position(*camera));
		
	}

	void draw(double dt) override
	{
		renderer->begin();
		renderer->draw(dt, *bg_mesh, *bg_transform);
		renderer->draw(dt, *vbuffer, tr);
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
	app.set_target_fps(60);
	
	app.get_scene_manager().create<MyScene>("arthur");
	app.get_scene_manager().set_current("arthur");

	app.run();
	return 0;
}
