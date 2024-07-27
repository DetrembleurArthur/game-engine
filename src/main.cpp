#include <ge/ge.hpp>
#include <chrono>
#include <ctime>



class MyScene : public ge::Scene
{
public:
	using ge::Scene::Scene;

	ge::Rect *player;

	ge::KeyCombo up;
	ge::KeyCombo down;
	ge::KeyCombo left;
	ge::KeyCombo right;

	ge::ProgressBar *hp;

	void init() override
	{
		ge::KeyEvents::add_combo(ge::KeyCombo()
			.combine(GLFW_KEY_A)
			.on_released([this](){app.get_window().close();}));
		ge::Application::get().set_controller_update_state(false);

		sounds->load("./res/sounds/blob.ogg", "blob");
		sounds->load("./res/sounds/blob2.ogg", "blob2");
		sounds->load("./res/sounds/music.ogg", "music");
		sounds->as_music("music")->play();

		textures->load("./res/images/blob-standart-padd4.png", "blob");
		spritesheets->load(textures->get("blob"), 4, 4, 4, 4, true, "blob");
		spritesheets->get("blob")->define_sprite_set("down", 0);
		spritesheets->get("blob")->define_sprite_set("right", 1);
		spritesheets->get("blob")->define_sprite_set("left", 2);
		spritesheets->get("blob")->define_sprite_set("up", 3);
	
		player = new ge::Rect(100, 100, true, true);
		player->set_color(ge::Colors::GREEN);
		player->get_transform().set_center_origin();
		player->get_transform().set_center_position(glm::vec2(0, 0));
		camera->focus(player->get_transform().get_center_position());

		player->get_component<ge::RendererComponent>().set_renderer(renderers->get("tex"));
		player->get_component<ge::SpriteComponent>().set_spritesheet(spritesheets->get("blob"));
		player->get_component<ge::SpriteComponent>().set_sprite_set("down");
		player->get_component<ge::SpriteComponent>().set_frequency(5);
		player->get_component<ge::SoundComponent>().add("blob", sounds->get("blob"), true);
		player->get_component<ge::SoundComponent>().add("blob2", sounds->get("blob2"), true);
		player->get_component<ge::SoundComponent>().get("blob2")->loop();

		up.combine("up");
		down.combine("down");
		left.combine("left");
		right.combine("right");

		player->get_component<ge::CallbackComponent>().set([this](float dt) {
			//get_camera()->focus(player->get_transform().get_center_position());
			bool multiple_keys = false;
			glm::vec2 pos = player->get_transform().get_center_position();
			up.run();
			if(up.is_pressed(true))
			{
				player->get_component<ge::SpriteComponent>().set_sprite_set("up");
				pos.y += -200 * dt;
				multiple_keys = true;
			}
			down.run();
			if(down.is_pressed(true))
			{
				if(!multiple_keys)
					player->get_component<ge::SpriteComponent>().set_sprite_set("down");
				pos.y += 200 * dt;
				multiple_keys = true;
			}
			left.run();
			if(left.is_pressed(true))
			{
				if(!multiple_keys)
					player->get_component<ge::SpriteComponent>().set_sprite_set("left");
				pos.x += -200 * dt;
				multiple_keys = true;
			}
			right.run();
			if(right.is_pressed(true))
			{
				if(!multiple_keys)
					player->get_component<ge::SpriteComponent>().set_sprite_set("right");
				pos.x +=  200 * dt;
				multiple_keys = true;
			}
			player->get_transform().set_center_position(pos);
			if(multiple_keys)
			{
				player->get_component<ge::SoundComponent>().play("blob2", true);
				player->get_component<ge::SpriteComponent>().set_frequency(5);
			}
			else
			{
				player->get_component<ge::SpriteComponent>().set_frequency(3);
				player->get_component<ge::SoundComponent>().get("blob2")->stop();
			}
		});

		hp = new ge::ProgressBar(0, 100, 1.0f, false, false);
		hp->set_border(5, 5);
		hp->set_size(75, 15);
		hp->get_root().get_transform().set_center_origin();

		hp->get_component<ge::CallbackComponent>().set([this](float dt) {
			glm::vec2 pos = player->get_transform().get_center_position();
			hp->set_position(pos.x, pos.y - 45);
		});

		add(player);
		add(hp);
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
