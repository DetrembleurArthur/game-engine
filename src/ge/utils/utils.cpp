#include "ge/utils/utils.hpp"
#include <ge/core/application.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <algorithm>

std::pair<std::string, std::string> ge::utils::name_and_ext(const std::string &filename)
{
    std::pair<std::string, std::string> pair = {filename, ""};
    std::size_t dotPos = filename.rfind('.');
    if (dotPos != std::string::npos)
    {
        pair.first = filename.substr(0, dotPos);
        pair.second = filename.substr(dotPos + 1);
    }
    return pair;
}

glm::vec2 ge::utils::screen_to_world(glm::vec2 screen, Camera2D &camera)
{
    glm::vec4 viewport = ge::Application::get().get_viewport();
    glm::vec2 position = screen - glm::vec2(viewport.x, viewport.y); // Ajustement des coordonnées

    glm::vec2 norm = position / glm::vec2(viewport.z, viewport.w);  // Normalisation
    norm = norm * glm::vec2(2.0f, 2.0f) - glm::vec2(1.0f, 1.0f);    // Transformation en espace NDC [-1, 1]

    glm::vec4 worldPos = glm::vec4(norm.x, -norm.y, 0.0f, 1.0f);  // Ajustement pour Y inversé
    worldPos = glm::inverse(camera.get_projection()) * worldPos;  // Inverse de la projection
    worldPos = glm::inverse(camera.get_view()) * worldPos;  
    return glm::vec2(worldPos.x, worldPos.y);
}

void ge::utils::reverse_words(std::string& sentence)
{
    std::vector<std::string> tokens;
    std::istringstream iss(sentence);
    std::string token;
    while (std::getline(iss, token, '\n'))
    {
        tokens.push_back(token);
    }
    std::reverse(tokens.begin(), tokens.end());
    std::ostringstream oss;
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        if (i != 0)
        {
            oss << '\n';
        }
        oss << tokens[i];
    }
    sentence = oss.str();
}

glm::vec2 ge::utils::rotate_around(glm::vec2 rotable, glm::vec2 rot_point, float angle)
{
    angle = glm::radians(angle);
    rotable -= rot_point;
    rotable = glm::vec2(rotable.x * cos(angle) - rotable.y * sin(angle), rotable.x * sin(angle) + rotable.y * cos(angle));
    rotable  += rot_point;
    return rotable;
}
