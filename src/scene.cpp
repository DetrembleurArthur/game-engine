#include "scene.hpp"
#include <log.hpp>

ge::Scene::Scene(const std::string& name) : name(name)
{
}

ge::Scene::~Scene()
{
    
}

std::string ge::Scene::get_name()
{
    return name;
}
