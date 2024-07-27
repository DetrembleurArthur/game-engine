#ifndef __GE_SCENE_HPP__
#define __GE_SCENE_HPP__
#include <string>
#include <ge/graphics/mesh.hpp>
#include <ge/core/renderer_manager.hpp>
#include <ge/core/texture_manager.hpp>
#include <ge/core/font_manager.hpp>
#include <ge/core/spritesheet_manager.hpp>
#include <vector>
#include <ge/core/sound_manager.hpp>
#include <ge/entity/game_object.hpp>

namespace ge
{
    class Application;
    enum Layers
    {
        BG=0,
        MAIN=1,
        UI=2
    };

    namespace rend
    {
        const std::string basic = "default";
        const std::string tex = "tex";
        const std::string text = "text";
    }

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
        Application& app;
        std::string name;
        Camera2D *camera = nullptr;
        Camera2D *ui_camera = nullptr;
        RendererManager *renderers=nullptr;
        TextureManager *textures = nullptr;
        FontManager *fonts = nullptr;
        SpritesheetManager *spritesheets=nullptr;
        SoundManager *sounds=nullptr;
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
        void kill(GameObject& go, int layer_id=Layers::MAIN);
        void kill(GameObject* go=nullptr, int layer_id=Layers::MAIN);
        std::string get_name();
        Camera2D *get_camera();
        Camera2D *get_ui_camera();
        glm::vec2 get_mp();
        void add(GameObject& go, int layer_id=0, GoInfos infos={false});
        void add(GameObject* go, int layer_id=0, GoInfos infos={true});
    };
}

#endif
