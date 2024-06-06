#ifndef __GE_UTILS_HPP__
#define __GE_UTILS_HPP__
#include <glm/glm.hpp>
#include <camera2D.hpp>

namespace ge
{
    namespace utils
    {
        glm::vec2 screen_to_world(glm::vec2 position, Camera2D& camera);
    }
}


#endif
