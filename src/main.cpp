#include <ge/ge.hpp>
#include <chrono>
#include <ctime>

//shell:startup

class MyScene : public ge::Scene
{
public:
	using ge::Scene::Scene;

	ge::Rect *rect;
	ge::Rect *x_axis;
	ge::Rect *y_axis;

	void init() override
	{
		ge::KeyEvents::add_combo(ge::KeyCombo()
			.combine(GLFW_KEY_A)
			.on_released([this](){app.get_window().close();}));
		ge::Application::get().set_controller_update_state(false);

		rect = new ge::Rect(100, 100);
		rect->get_transform().set_position(300, 300);
		rect->set_color(ge::Colors::RED);
		rect->get_transform().set_center_origin();

		x_axis = new ge::Rect(30, 30);
		x_axis->get_transform().set_position(0, 100);
		x_axis->set_color(ge::Colors::BLUE);
		x_axis->get_transform().set_center_origin();

		y_axis = new ge::Rect(30, 30);
		y_axis->get_transform().set_position(100, 0);
		y_axis->set_color(ge::Colors::BLUE);
		y_axis->get_transform().set_center_origin();

		rect->get_component<ge::ShapePropertiesComponent>().x().link(x_axis->get_component<ge::ShapePropertiesComponent>().p_x());
		rect->get_component<ge::ShapePropertiesComponent>().y().link(y_axis->get_component<ge::ShapePropertiesComponent>().p_y());

		rect->get_component<ge::EventsComponent>().dragging(ge::DragMode::TWO_AXIS, true).use_collider();

		rect->get_component<ge::MoveComponent>().rotation_speed = 45;


		add(x_axis);
		add(y_axis);
		add(rect);
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
