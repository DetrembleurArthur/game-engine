#ifndef __GE_UTILS_HPP__
#define __GE_UTILS_HPP__
#include <glm/glm.hpp>
#include <ge/graphics/camera2D.hpp>
#include <utility>
#include <string>

namespace ge
{
    namespace utils
    {
        std::pair<std::string, std::string> name_and_ext(const std::string& filename);
        glm::vec2 screen_to_world(glm::vec2 position, Camera2D& camera);
        void reverse_words(std::string& sentence);
        glm::vec2 rotate_around(glm::vec2 rotable, glm::vec2 rot_point, float angle);
    }
}


#endif
