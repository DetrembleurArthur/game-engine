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
		fonts->load("./res/fonts/atop.ttf", "atop", 100);
		textures->load("./res/images/blob-standart-padd4.png", "blob");

		ge::Text *text = new ge::Text("Hello world !\nI am Arthur Detrembleur", fonts->get("atop"), 10);
		text->set_color(ge::Colors::MAGENTA);
		text->set_text_height(100);
		text->get_transform().set_center_origin();
		text->enable_shadow();
		text->set_shadow_color(ge::Colors::BLACK);
		text->set_shadow_offset(glm::vec2(2, 2));
		text->get_component<ge::MoveComponent>().rotation_speed = 90;

		text->get_component<ge::ColliderComponent>().fit_collider(glm::vec2(1, 1));

		ge::Rect *text_collider = text->get_component<ge::ColliderComponent>().create_rendered_collider();
		text->get_component<ge::CallbackComponent>().set([text, text_collider, this](float dt) {
			text->get_transform().set_position(ge::MouseInput::get_position(get_camera()));
			text->get_component<ge::ColliderComponent>().update_rendered_collider(text_collider);
		});

		add(text, ge::Layers::MAIN);
		add(text_collider, ge::Layers::MAIN);

		spritesheets->load(textures->get("blob"), 4, 4, 4, 4, true, "blob");
		ge::SpriteSheet *ss = spritesheets->get("blob");
		ss->define_sprite_set("down", 0);
		ss->define_sprite_set("right", 1);
		ss->define_sprite_set("left", 2);
		ss->define_sprite_set("up", 3);


		ge::Rect *rect = new ge::Rect(200, 200, true, true);
		rect->get_transform().set_position(300, 300);
		rect->get_transform().set_center_origin();
		rect->set_color(ge::Colors::LIME);
		auto& sc = rect->get_component<ge::SpriteComponent>();
		sc.set_frequency(10);
		sc.set_spritesheet(ss);
		sc.set_sprite_set("down");

		rect->get_component<ge::ColliderComponent>().fit_collider(glm::vec2(0.9,0.50), glm::vec2(0.5, 0.85));

		ge::Rect *c = rect->get_component<ge::ColliderComponent>().create_rendered_collider();
		

		rect->get_component<ge::CallbackComponent>().set([this, rect, c, text](float dt) {
			rect->get_component<ge::ColliderComponent>().update_rendered_collider(c);
			if(ge::KeyInput::is_pressed(GLFW_KEY_RIGHT))
			{
				rect->get_component<ge::MoveComponent>().speed = glm::vec2(300, 0);
				rect->get_component<ge::SpriteComponent>().set_sprite_set("right");
			}
			else if(ge::KeyInput::is_pressed(GLFW_KEY_LEFT))
			{
				rect->get_component<ge::MoveComponent>().speed = glm::vec2(-300, 0);
				rect->get_component<ge::SpriteComponent>().set_sprite_set("left");
			}
			else if(ge::KeyInput::is_pressed(GLFW_KEY_UP))
			{
				rect->get_component<ge::MoveComponent>().speed = glm::vec2(0, -300);
				rect->get_component<ge::SpriteComponent>().set_sprite_set("up");
			}
			else if(ge::KeyInput::is_pressed(GLFW_KEY_DOWN))
			{
				rect->get_component<ge::MoveComponent>().speed = glm::vec2(0, 300);
				rect->get_component<ge::SpriteComponent>().set_sprite_set("down");
			}
			else
			{
				rect->get_component<ge::MoveComponent>().speed = glm::vec2(0);
			}
			if(rect->get_component<ge::ColliderComponent>().contains(ge::MouseInput::get_position(get_camera())))
			{
				rect->set_color(ge::Colors::GOLD);
			}
			else
			{
				rect->set_color(ge::Colors::LIME);
			}
			if(rect->get_component<ge::ColliderComponent>().contains(text->get_component<ge::ColliderComponent>()))
			{
				text->set_color(ge::Colors::GOLD);
			}
			else
			{
				text->set_color(ge::Colors::LIME);
			}
		});


		
		

		



		add(rect, ge::Layers::MAIN);
		add(c, ge::Layers::MAIN);
		

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
