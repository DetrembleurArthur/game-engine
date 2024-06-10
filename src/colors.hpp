#ifndef __GE_COLORS_HPP__
#define __GE_COLORS_HPP__
#include <glm/glm.hpp>

namespace ge
{
    using Color = glm::vec4;
    namespace Colors
    {
        const Color RED(1.0f, 0.0f, 0.0f, 1.0f);
        const Color GREEN(0.0f, 1.0f, 0.0f, 1.0f);
        const Color BLUE(0.0f, 0.0f, 1.0f, 1.0f);
        const Color WHITE(1.0f, 1.0f, 1.0f, 1.0f);
        const Color BLACK(0.0f, 0.0f, 0.0f, 1.0f);
        const Color YELLOW(1.0f, 1.0f, 0.0f, 1.0f);
        const Color CYAN(0.0f, 1.0f, 1.0f, 1.0f);
        const Color MAGENTA(1.0f, 0.0f, 1.0f, 1.0f);
        const Color GRAY(0.5f, 0.5f, 0.5f, 1.0f);
        const Color ORANGE(1.0f, 0.5f, 0.0f, 1.0f);
        const Color PURPLE(0.5f, 0.0f, 0.5f, 1.0f);
        const Color BROWN(0.6f, 0.3f, 0.0f, 1.0f);
        const Color PINK(1.0f, 0.75f, 0.8f, 1.0f);
        const Color LIME(0.0f, 1.0f, 0.0f, 1.0f);
        const Color NAVY(0.0f, 0.0f, 0.5f, 1.0f);
        const Color TEAL(0.0f, 0.5f, 0.5f, 1.0f);
        const Color OLIVE(0.5f, 0.5f, 0.0f, 1.0f);
        const Color MAROON(0.5f, 0.0f, 0.0f, 1.0f);
        const Color SILVER(0.75f, 0.75f, 0.75f, 1.0f);
        const Color GOLD(1.0f, 0.84f, 0.0f, 1.0f);
    }
}


#endif
