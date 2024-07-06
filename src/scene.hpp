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
    enum Layers
    {
        BG=0,
        MAIN=1,
        UI=2
    };

    struct GoInfos
    {
        bool freeable=true;
    };

    struct LayerInfos
    {
        bool kill_enabled=false;
    };

    using Layer=std::pair<std::vector<std::pair<GameObject *, GoInfos>>, LayerInfos>;

    class Scene
    {
    protected:
        std::string name;
        Camera2D *camera = nullptr;
        Renderer *renderer = nullptr;
        TextureManager *textures = nullptr;
        std::vector<Layer> layers;
    public:
        Scene(const std::string& name, int layers_number=3);
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
        void kill(GameObject& go, int layer_id=0);
        void kill(GameObject* go=nullptr, int layer_id=0);
        std::string get_name();
        Camera2D *get_camera();
        void add(GameObject& go, int layer_id=0, GoInfos infos={false});
        void add(GameObject* go, int layer_id=0, GoInfos infos={true});
    };
}

#endif
