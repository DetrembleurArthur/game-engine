#include "scene_manager.hpp"

void ge::SceneManager::set_current(const std::string &name)
{
    log(name + " swap to current scene", LogLevels::SCENE);
    if(scenes.find(name) != scenes.end())
    {
        if(current)
        {
            current->unload();
            log("unload " + current->get_name(), LogLevels::SCENE);
        }
        current = scenes[name];
        current->load();
        log("load " + name, LogLevels::SCENE);
    }
}

ge::Scene *ge::SceneManager::get_current()
{
    return current;
}

void ge::SceneManager::delete_scenes()
{
    current->unload();
    log("unload " + current->get_name(), LogLevels::SCENE);
    current = nullptr;
    for(auto it = scenes.begin(); it != scenes.end(); it++)
    {
        if(it->second)
        {
            log("destroy " + it->second->get_name(), LogLevels::SCENE);
            it->second->destroy();
            delete it->second;
            it->second = nullptr;
        }
    }
    scenes.clear();
}
