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
	ge::Rect *bg;
	ge::Map *map;

	ge::Slider *slider;

	void init() override
	{
		ge::KeyEvents::add_combo(ge::KeyCombo()
			.combine(GLFW_KEY_A)
			.combine(GLFW_KEY_LEFT_CONTROL)
			.on_released([this](){app.get_window().close();}));
		ge::Application::get().set_controller_update_state(false);

		sounds->load("./res/sounds/blob.ogg", "blob");
		sounds->load("./res/sounds/blob2.ogg", "blob2");
		sounds->load("./res/sounds/music.ogg", "music");

		textures->load("./res/images/floor.png", "bloc");
		textures->load("./res/images/wall.png", "wall");
		textures->load("./res/images/blob-standart-padd4.png", "blob");
		spritesheets->load(textures->get("blob"), 4, 4, 4, 4, true, "blob");
		spritesheets->get("blob")->define_sprite_set("down", 0);
		spritesheets->get("blob")->define_sprite_set("right", 1);
		spritesheets->get("blob")->define_sprite_set("left", 2);
		spritesheets->get("blob")->define_sprite_set("up", 3);
	
		map = new ge::Map("./res/map/test.txt", glm::vec2(128));
		map->load();

	}

	void destroy() override
	{
		delete map;
	}

	void load() override
	{
		//sounds->as_music("music")->play();
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
			bool multiple_keys = false;
			glm::vec2 pos = player->get_transform().get_center_position();
			glm::vec2 old = pos;
			glm::vec2 speed(0, 0);
			up.run();
			if(up.is_pressed(true))
			{
				player->get_component<ge::SpriteComponent>().set_sprite_set("up");
				speed.y += -300 * dt;
				multiple_keys = true;
			}
			down.run();
			if(down.is_pressed(true))
			{
				if(!multiple_keys)
					player->get_component<ge::SpriteComponent>().set_sprite_set("down");
				speed.y += 300 * dt;
				multiple_keys = true;
			}
			left.run();
			if(left.is_pressed(true))
			{
				if(!multiple_keys)
					player->get_component<ge::SpriteComponent>().set_sprite_set("left");
				speed.x += -300 * dt;
				multiple_keys = true;
			}
			right.run();
			if(right.is_pressed(true))
			{
				if(!multiple_keys)
					player->get_component<ge::SpriteComponent>().set_sprite_set("right");
				speed.x +=  300 * dt;
				multiple_keys = true;
			}
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
			
			player->get_transform().set_center_position(pos+speed);
			
			glm::vec2&& delta = get_camera()->focus(pos);
			bg->move_tex(delta * glm::vec2(get_camera()->get_zoom().x));
		});

		hp = new ge::ProgressBar(0, 100, 1.0f, false, false);
		hp->set_border(5, 5);
		hp->set_size(75, 15);
		hp->get_root().get_transform().set_center_origin();

		hp->get_component<ge::CallbackComponent>().set([this](float dt) {
			glm::vec2 pos = player->get_transform().get_center_position();
			hp->set_position(pos.x, pos.y - 45);
			hp->set_value(hp->get_value() + 10*dt);
		});

		player->get_component<ge::ColliderComponent>().fit_collider(glm::vec2(0.8, 0.5), glm::vec2(0.5, 1));

		bg = new ge::Rect(textures->get("bloc"), true);
		bg->create_component<ge::RendererComponent>().set_renderer(renderers->get("tex_ui"));
		bg->get_transform().set_size(1400, 787);
		bg->get_transform().set_position(0, 0);
		bg->set_color(ge::Colors::WHITE);

		get_camera()->get_zoom() = glm::vec3(0.8);

		map->foreach([this](int type, glm::vec2 pos, glm::vec2 size) {
			ge::Rect *wall=nullptr;
			switch(type)
			{
				case 1:
					wall = new ge::Rect(textures->get("wall"));
					wall->create_component<ge::RendererComponent>().set_renderer(renderers->get("tex"));
					wall->get_transform().set_size(size.x, size.y);
					wall->get_transform().set_tl_position(pos);
					wall->get_transform().set_center_origin();
					wall->set_color(ge::Colors::rand());
					wall->get_component<ge::ColliderComponent>().fit_collider();
					wall->get_component<ge::CallbackComponent>().set([this, wall](float dt) {
						glm::vec2 pos = player->get_transform().get_center_position();
						if(player->get_component<ge::ColliderComponent>().straight_contains(wall->get_component<ge::ColliderComponent>()))
						{
							glm::vec2 vec = player->get_component<ge::ColliderComponent>().resolve_straight_collision(wall->get_component<ge::ColliderComponent>());
							pos += vec;
							player->get_transform().set_center_position(pos);
							hp->set_value(hp->get_value() - 30*dt);
						}
					});
					//if(rand()%2)wall->get_component<ge::AnimationComponent>().to_size(1.5, glm::vec2(128, 128), glm::vec2(0, 0), -1, true, ge::tweenf::ease_in_out_quad);
					
					wall->get_component<ge::EventsComponent>().dragging();
					add(wall, ge::Layers::MAIN);
					break;
				case 2:
					player->get_transform().set_center_position(pos);
					break;
			}
		});

		slider = new ge::Slider(200, 5, 50, 150, 75);
		slider->set_position(700, 450);


		add(bg, ge::Layers::BG);
		add(player, ge::Layers::MAIN);
		add(hp, ge::Layers::MAIN);
		add(slider, ge::Layers::UI);
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
	app.get_window().set_clear_color(ge::Colors::BLACK);
	app.set_target_fps(0);
	app.get_window().set_aspect_ratio(16, 9);
	
	app.get_scene_manager().create<MyScene>("arthur");
	app.get_scene_manager().set_current("arthur");

	app.run();
	return 0;
}
