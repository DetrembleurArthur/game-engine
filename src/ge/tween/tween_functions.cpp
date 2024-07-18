#include "ge/tween/tween_functions.hpp"
#include <glm/glm.hpp>
#define PI 3.14159265358979323846264338327950288

float ge::tweenf::linear(float x)
{
    return x;
}

float ge::tweenf::ease_in_sine(float x)
{
    return 1.0 - cos(x * PI / 2.0);
}

float ge::tweenf::ease_ousine(float x)
{
    return sin(x * PI / 2);
}

float ge::tweenf::ease_in_cubic(float x)
{
    return x * x * x;
}

float ge::tweenf::ease_out_cubic(float x)
{
    return 1.0 - pow(1 - x, 3);
}

float ge::tweenf::ease_in_out_cubic(float x)
{
    return x < 0.5 ? 4 * x * x * x : 1.0 - pow(-2 * x + 2, 3) / 2.0;
}

float ge::tweenf::ease_in_quint(float x)
{
    return x * x * x * x * x;
}

float ge::tweenf::ease_out_quint(float x)
{
    1 - pow(1 - x, 5);
}

float ge::tweenf::ease_in_out_quint(float x)
{
    return x < 0.5 ? 16 * x * x * x * x * x : 1 - pow(-2 * x + 2, 5) / 2;
}

float ge::tweenf::ease_in_circ(float x)
{
    return 1 - sqrt(1 - pow(x, 2));
}

float ge::tweenf::ease_out_circ(float x)
{
    return sqrt(1 - pow(x - 1, 2));
}

float ge::tweenf::ease_in_out_circ(float x)
{
    return x < 0.5
        ? (1 - sqrt(1 - pow(2 * x, 2))) / 2
        : (sqrt(1 - pow(-2 * x + 2, 2)) + 1) / 2;
}

float ge::tweenf::ease_in_elastic(float x)
{
    const float c4 = (2 * PI) / 3;
    return x == 0
        ? 0
        : x == 1
        ? 1
        : -pow(2, 10 * x - 10) * sin((x * 10 - 10.75) * c4);
}

float ge::tweenf::ease_out_elastic(float x)
{
    const float c4 = (2 * PI) / 3;
    return x == 0
        ? 0
        : x == 1
        ? 1
        : pow(2, -10 * x) * sin((x * 10 - 0.75) * c4) + 1;
}

float ge::tweenf::ease_in_out_elastic(float x)
{
    const float c5 = (2 * PI) / 4.5f;
    return x == 0
        ? 0
        : x == 1
        ? 1
        : x < 0.5
        ? -(pow(2, 20 * x - 10) * sin((20 * x - 11.125) * c5)) / 2
        : (pow(2, -20 * x + 10) * sin((20 * x - 11.125) * c5)) / 2 + 1;
}

float ge::tweenf::ease_in_quad(float x)
{
    return x * x;
}

float ge::tweenf::ease_out_quad(float x)
{
    return 1 - (1 - x) * (1 - x);
}

float ge::tweenf::ease_in_out_quad(float x)
{
	return x < 0.5 ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2;
}

float ge::tweenf::ease_in_quart(float x)
{
    return x * x * x * x;
}

float ge::tweenf::ease_out_quart(float x)
{
    return 1 - pow(1 - x, 4);
}

float ge::tweenf::ease_in_out_quart(float x)
{
    return x < 0.5 ? 8 * x * x * x * x : 1 - pow(-2 * x + 2, 4) / 2;
}

float ge::tweenf::ease_in_expo(float x)
{
	return x == 0 ? 0 : pow(2, 10 * x - 10);
}

float ge::tweenf::ease_out_expo(float x)
{
    return x == 1 ? 1 : 1 - pow(2, -10 * x);
}

float ge::tweenf::ease_in_out_expo(float x)
{
    return x == 0
        ? 0
        : x == 1
        ? 1
        : x < 0.5 ? pow(2, 20 * x - 10) / 2
        : (2 - pow(2, -20 * x + 10)) / 2;
}

float ge::tweenf::ease_in_back(float x)
{
    const float c1 = 1.70158f;
    const float c3 = c1 + 1;
    return c3 * x * x * x - c1 * x * x;
}

float ge::tweenf::ease_out_back(float x)
{
    const float c1 = 1.70158f;
    const float c3 = c1 + 1;
    return 1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2);
}

float ge::tweenf::ease_in_out_back(float x)
{
    const float c1 = 1.70158f;
    const float c2 = c1 + 1.525f;
    return x < 0.5
            ? (pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2
            : (pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2;
}

float ge::tweenf::ease_in_bounce(float x)
{
    return 1 - ease_out_bounce(1 - x);
}

float ge::tweenf::ease_out_bounce(float x)
{
    const float n1 = 7.5625f;
    const float d1 = 2.75f;
    if (x < 1 / d1)
        return n1 * x * x;
    else if (x < 2 / d1)
        return n1 * (x -= 1.5 / d1) * x + 0.75f;
    else if (x < 2.5 / d1)
        return n1 * (x -= 2.25 / d1) * x + 0.9375f;
    else
        return n1 * (x -= 2.625 / d1) * x + 0.984375f;
}

float ge::tweenf::ease_in_out_bounce(float x)
{
    return x < 0.5
        ? (1 - ease_out_bounce(1 - 2 * x)) / 2
        : (1 + ease_out_bounce(2 * x - 1)) / 2;
}



