#ifndef __GE_GAME_OBJECT_HPP__
#define __GE_GAME_OBJECT_HPP__
#include <mesh.hpp>
#include <texture.hpp>
#include <transform.hpp>
#include <component.hpp>
#include <vector>
#include <colors.hpp>

namespace ge
{
    class GameObject
    {
    private:
        Color color;
        Mesh *mesh=nullptr;
        const Texture *texture=nullptr;
        Transform transform;
        std::vector<Component *> components;
    public:
        GameObject();
        virtual ~GameObject();
        void as_rect(float width, float height);
        void as_rect(const Texture *texture);
        void as_circle(int points, float radius);
        void as_circle(int points, const Texture *texture);
        void set_color(Color color);
        Color& get_color();
        Mesh *get_mesh();
        const Texture *get_texture();
        Transform& get_transform();
        virtual void update(float dt);
        bool drawable();
        template <typename T> T& create_component()
        {
            static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
            for(Component *c : components)
            {
                if(dynamic_cast<T *>(c))
                {
                    log("component must be created once by game objet", LogLevels::WARNING);
                    return *dynamic_cast<T *>(c);
                }
            }
            T *c = new T(this);
            components.push_back(c);
            return *c;
        }

        template <typename T> T& get_component()
        {
            static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
            for(Component *c : components)
            {
                if(dynamic_cast<T *>(c))
                {
                    return *c;
                }
            }
            log("component does not exists", LogLevels::ERROR);
            return Component();
        }

        template <typename T> void remove_component()
        {
            static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
            int i = 0;
            for(Component *c : components)
            {
                if(dynamic_cast<T *>(c))
                {
                    break;
                }
                i++;
            }
            if(i < components.size())
                components.erase(components.begin() + i);
        }
    };
}



#endif

