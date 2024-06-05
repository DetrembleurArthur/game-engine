#ifndef __GE_SCENE_HPP__
#define __GE_SCENE_HPP__
#include <string>
#include <renderer.hpp>

namespace ge
{
    class Scene
    {
    protected:
        std::string name;
        Renderer *renderer = nullptr;
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
        virtual void update(double dt) = 0;
        virtual void draw(double dt) = 0;
        void set_renderer(ge::Renderer *renderer);
        std::string get_name();
    };
}

#endif
