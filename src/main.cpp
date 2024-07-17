#include <ge/ge.hpp>


class MyScene : public ge::Scene
{
public:
	using ge::Scene::Scene;

	ge::Text *text;
	ge::Vec2NotifyProperty snp;
	ge::Node *node;

	void init() override
	{
		ge::KeyEvents::add_combo(ge::KeyCombo()
			.combine(GLFW_KEY_A)
			.on_released([this](){app.get_window().close();}));
		ge::Application::get().set_controller_update_state(false);

		fonts->load("./res/fonts/atop.ttf", "atop", 100);

		text = new ge::Text("test", fonts->get("atop"));
		text->get_transform().set_center_position(glm::vec2(500, 300));

		snp.link<std::string>(text->get_component<ge::TextPropertiesComponent>().p_text(), [](glm::vec2 mp) {
			return std::to_string((int)mp.x) +", " + std::to_string((int)mp.y);
		});

		node = new ge::Node();
		node->get_component<ge::CallbackComponent>().set([this](float dt) {
			auto&& mp = get_mp();
			snp.set(mp);
		});


		add(text);
		add(node);


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
