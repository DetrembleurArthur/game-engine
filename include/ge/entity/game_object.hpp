#ifndef __GE_GAME_OBJECT_HPP__
#define __GE_GAME_OBJECT_HPP__

#include <ge/entity/transform.hpp>
#include <ge/entity/components/component.hpp>
#include <vector>
#include <ge/utils/log.hpp>


namespace ge
{
    struct GOFlags
    {
        bool disabled: 1;
        bool killed : 1;
    };

    class GameObject
    {
    protected:
        Transform transform;
        std::vector<Component *> components;
        GOFlags flags;
    public:
        GameObject();
        virtual ~GameObject();
        Transform& get_transform();
        virtual void update(float dt);
        GOFlags& get_flags();
        operator Transform&();
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

