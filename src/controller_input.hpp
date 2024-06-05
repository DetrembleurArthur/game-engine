#ifndef __GE_CONTROLLER_INPUT_HPP__
#define __GE_CONTROLLER_INPUT_HPP__
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <vector>

namespace ge
{
    class Controller
    {
    private:
        int id;
        std::vector<float> axes;
        std::vector<unsigned char> buttons;
        std::vector<unsigned char> hats;
    public:
        struct {
            unsigned char a;
            unsigned char b;
            unsigned char x;
            unsigned char y;
            unsigned char lb;
            unsigned char rb;
            unsigned char select;
            unsigned char start;
            unsigned char guide;
            unsigned char lclick;
            unsigned char rclick;
            unsigned char up;
            unsigned char right;
            unsigned char down;
            unsigned char left;
        } gamepad_buttons;
        struct {
            float left_x;
            float left_y;
            float right_x;
            float right_y;
            float left_trigger;
            float right_trigger;
        } gamepad_axes;
        Controller(int id=-1);
        std::vector<float>& get_axes(bool extract=true);
        std::vector<unsigned char>& get_buttons(bool extract=true);
        std::vector<unsigned char>& get_hats(bool extract=true);
        std::string get_name();
        bool is_gamepad();
        std::string get_gamepad_name();
        void update_gamepad();
    };

    class ControllerInput
    {
    private:
        static std::unordered_map<int, Controller> controllers;
    public:
        static bool is_present(int joystick_id=GLFW_JOYSTICK_1);
        static Controller& get(int jid=-1);
        static void activate(int jid);
        static void disactivate(int jid);
        static void update_controllers();
    };
}

#endif

