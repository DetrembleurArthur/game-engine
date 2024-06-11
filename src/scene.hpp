#ifndef __GE_SCENE_HPP__
#define __GE_SCENE_HPP__
#include <string>
#include <mesh.hpp>
#include <renderer.hpp>
#include <texture_manager.hpp>
#include <vector>
#include <game_object.hpp>

namespace ge
{
    struct GoInfos
    {
        bool freeable=true;
    };

    class Scene
    {
    protected:
        std::string name;
        Camera2D *camera = nullptr;
        Renderer *renderer = nullptr;
        TextureManager *textures = nullptr;
        std::vector<std::pair<GameObject *, GoInfos>> game_objects;
        bool enable_go_kill=false;
    public:
        Scene(const std::string& name);
        virtual ~Scene();
        // call once at the begining
        virtual void init() = 0;
        // call once at the end
        virtual void destroy() = 0;
        // call at scene switching
        virtual void load() = 0;
        // call at scene switching
        virtual void unload() = 0;
        virtual void update(double dt);
        virtual void draw(double dt);
        void set_renderer(ge::Renderer *renderer);
        void kill(GameObject& go);
        void kill(GameObject* go=nullptr);
        std::string get_name();
        Camera2D *get_camera();
        void add(GameObject& go, GoInfos infos={false});
        void add(GameObject* go, GoInfos infos={true});
    };
}

#endif
