#include <ge/ge.hpp>
#include <chrono>
#include <ctime>

void get_current_time(int &hour, int &minute, int &second) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm;
#ifdef _WIN32
    localtime_s(&now_tm, &now_time_t); // Pour les systèmes Windows
#else
    localtime_r(&now_time_t, &now_tm); // Pour les systèmes POSIX
#endif
    hour = now_tm.tm_hour;
    minute = now_tm.tm_min;
    second = now_tm.tm_sec;
}

class MyScene : public ge::Scene
{
public:
	using ge::Scene::Scene;

	ge::Rect *hour;
	ge::Rect *minute;
	ge::Rect *seconde;
	ge::Rect *outer;
	ge::Circle *center;
	ge::Node *clock;
	ge::FloatNotifyProperty hour_property;
	ge::FloatNotifyProperty minute_property;
	ge::FloatNotifyProperty seconde_property;
	ge::Text *time_text;

	void init() override
	{
		ge::KeyEvents::add_combo(ge::KeyCombo()
			.combine(GLFW_KEY_A)
			.on_released([this](){app.get_window().close();}));
		ge::Application::get().set_controller_update_state(false);

		textures->load("./res/images/clock.png", "clock");

		clock = new ge::Node();
		outer = new ge::Rect(textures->get("clock"));
		outer->get_transform().set_size(500, 500);
		outer->get_transform().set_position(glm::vec2(0, 0));
		outer->get_transform().set_center_origin();

		hour = new ge::Rect(150, 3);
		hour->set_color(ge::Colors::BLACK);
		hour->get_transform().set_position(glm::vec2(0, 0));
		hour->get_transform().set_origin(25, 1.5);

		minute = new ge::Rect(200, 5);
		minute->set_color(ge::Colors::GRAY);
		minute->get_transform().set_position(glm::vec2(0, 0));
		minute->get_transform().set_origin(30, 2.5);

		seconde = new ge::Rect(220, 2);
		seconde->set_color(ge::Colors::BLACK);
		seconde->get_transform().set_position(glm::vec2(0, 0));
		seconde->get_transform().set_origin(30, 2.5);

		center = new ge::Circle(6, 10);
		center->set_color(ge::Colors::RED);
		center->get_transform().set_position(glm::vec2(0, 0));
		center->get_transform().set_center_origin();

		fonts->load("./res/fonts/halo.otf", "atop", 100);
		time_text = new ge::Text("...", fonts->get("atop"));
		time_text->get_transform().set_position(15, 15);
		time_text->get_transform().set_tl_origin();
		time_text->set_text_align(ge::TextAlign::LEFT);
		time_text->set_text_height(18);
		
		clock->add(outer, true);
		clock->add(hour, true);
		clock->add(minute, true);
		clock->add(seconde, true);
		clock->add(center, true);
		clock->add(time_text, false);


		hour_property.set(0);
		minute_property.set(0);
		seconde_property.set(0);
		hour_property.link<float>(hour->get_component<ge::ShapePropertiesComponent>().p_rotation(), [](float hour) {
			return hour / 12.0 * 360.0 - 90;
		});
		hour_property.notify();

		minute_property.link<float>(minute->get_component<ge::ShapePropertiesComponent>().p_rotation(), [](float minute) {
			return minute / 60.0 * 360.0 - 90;
		});
		minute_property.notify();

		seconde_property.link<float>(seconde->get_component<ge::ShapePropertiesComponent>().p_rotation(), [](float seconde) {
			return seconde / 60.0 * 360.0 - 90;
		});
		seconde_property.notify();

		auto&& s = ge::Application::get().get_window().get_size();
		clock->get_transform().set_position(glm::vec2(s.x / 2, s.y / 2));
		clock->get_component<ge::CallbackComponent>().set([this](float dt) {
			int h, m, s;
			get_current_time(h, m, s);
			hour_property.set(h + m / 60.0);
			minute_property.set(m + s / 60.0);
			seconde_property.set(s);
			time_text->get_component<ge::TextPropertiesComponent>().text()
				.set(std::to_string(h) + "h " + std::to_string(m) + "m " + std::to_string(s) + "s");
			if(ge::MouseInput::get_state("left") == ge::ButtonState::PressedBtn)
			{
				auto&& s = ge::Application::get().get_window().get_size();
				auto&& pos = ge::MouseInput::get_position() + ge::Application::get().get_window().get_position();
				ge::Application::get().get_window().set_position(pos - glm::vec2(s.x/2, s.y/2));
			}
		});


		add(clock);
	}

	void destroy() override
	{
		
	}

	void load() override
	{
		//app.resize(1400, 900);
		//app.get_window().set_clear_color(ge::Colors::CYAN);

	}

	void unload() override
	{
		
	}

};


int main(int argc, char const *argv[])
{
	

	ge::Application app([]() {
		ge::Window::hint_floating(true);
		ge::Window::hint_decorated(false);
		ge::Window::hint_transparent_framebuffer(true);
	});
	app.init("Test app", 520, 520);
	app.get_window().set_icon("./res/images/ge-logo.png");
	app.get_window().set_clear_color(ge::Colors::BLACK);
	app.set_target_fps(0);
	
	app.get_scene_manager().create<MyScene>("arthur");
	app.get_scene_manager().set_current("arthur");

	app.run();
	return 0;
}
