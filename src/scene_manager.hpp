#ifndef __GE_SCENE_MANAGER_HPP__
#define __GE_SCENE_MANAGER_HPP__
#include <unordered_map>
#include <scene.hpp>
#include <log.hpp>

namespace ge
{
    class SceneManager
    {
    private:
        std::unordered_map<std::string, Scene *> scenes;
        Scene *current=nullptr;
    public:
        void set_current(const std::string& name);
        Scene *get_current();
        void delete_scenes();
        template <typename T> void create(const std::string& name, int layers_number=3)
        {
            static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");
            if(scenes.find(name) == scenes.end())
            {
                log("register " + name, LogLevels::SCENE);
                Scene *scene = new T(name, layers_number);
                scenes[name] = scene;
                log("init " + name, LogLevels::SCENE);
                scene->init();
            }
            else
            {
                log("can not register scene " + name, LogLevels::WARNING);
            }
        }
    };
}

#endif
