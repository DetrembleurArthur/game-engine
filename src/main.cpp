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

		ge::Rect *rect = new ge::Rect(100, 100, true, true);
		rect->get_transform().set_position(300, 300);
		rect->get_transform().set_center_origin();
		rect->set_color(ge::Colors::LIME);
		textures->load("./res/images/ge-logo.png", "logo");
		textures->load("./res/images/blob-standart.png", "blob");
		rect->set_texture(textures->get("blob"));

		ge::SpriteSheet ss(textures->get("blob"), 4, 4);
		ss.define_sprite_set("down", 0, 3);
		ss.define_sprite_set("right", 4, 7);
		ss.define_sprite_set("left", 8, 11);
		ss.define_sprite_set("up", 12, 15);

		rect->update_rect_uvs(ss.get_sprite_set("down")[0].uvs, ss.get_uvs_size());


		
		rect->get_component<ge::CallbackComponent>().set([rect, this](float dt) {
			rect->get_transform().set_position(ge::MouseInput::get_position(get_camera()));
		});

		ge::Circle *circle = new ge::Circle(30, textures->get("blob"), true);
		circle->set_radius(100);
		circle->set_color(ge::Colors::RED);
		circle->update_circle_uvs(ss.get_sprite_set("right")[0].uvs, ss.get_uvs_size());

		

		add(rect, ge::Layers::MAIN);
		add(circle, ge::Layers::MAIN);
		

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
