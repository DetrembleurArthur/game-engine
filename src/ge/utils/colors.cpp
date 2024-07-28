#include "ge/utils/colors.hpp"

ge::Color ge::Colors::rand()
{
    return Color((std::rand() % 100) / 100.0, (std::rand() % 100) / 100.0, (std::rand() % 100) / 100.0, 1.0);
}

ge::Color ge::Colors::randa()
{
    return Color((std::rand() % 100) / 100.0, (std::rand() % 100) / 100.0, (std::rand() % 100) / 100.0, (std::rand() % 100) / 100.0);
}
