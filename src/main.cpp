#include <ge.hpp>


class MyScene : public ge::Scene
{
public:
	using ge::Scene::Scene;

	ge::VertexBuffer vbuffer;
	ge::VertexBuffer vbuffer2;

	void init() override
	{
		ge::KeyEvents::add_combo(ge::KeyCombo()
			.combine(GLFW_KEY_A)
			.on_released([](){ge::Application::get().get_window().close();}));
		ge::Application::get().set_controller_update_state(false);


		float vertices[] = {
			0.0f, 0.0f, 0.0f,
			0.0f,  1, 0.0f,
			1, 1, 0.0f,
			1,  0, 0.0f
		};
		float vertices2[] = {
			 0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
		};
		unsigned elements[] = {
			0, 1, 2,
			0, 2, 3
		};
		vbuffer.fill(sizeof(vertices), vertices, sizeof(elements), elements);
		vbuffer2.fill(sizeof(vertices2), vertices2, sizeof(elements), elements);

		vbuffer.set_color(ge::Colors::BLUE);
		vbuffer2.set_color(ge::Colors::GREEN);

		
	}

	void destroy() override
	{
		
	}

	void load() override
	{
		ge::Application::get().get_window().set_clear_color(ge::Colors::RED);
		

	}

	void unload() override
	{
		
	}

	void update(double dt) override
	{
		
	}

	void draw(double dt) override
	{
		renderer->begin();
		renderer->draw(dt, vbuffer);
		renderer->draw(dt, vbuffer2);
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
