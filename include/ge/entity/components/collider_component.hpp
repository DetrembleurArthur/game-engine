#ifndef __GE_COLLIDER_COMPONENT_HPP__
#define __GE_COLLIDER_COMPONENT_HPP__
#include <ge/entity/components/component.hpp>
#include <ge/entity/transform.hpp>

namespace ge
{
    struct Collider
    {
        float x=0;
        float y=0;
        float width=0;
        float height=0;
        float angle=0;
        float dx=0;
        float dy=0;
        float dxf=0;
        float dyf=0;
        float wf=0;
        float hf=0;
        glm::vec2 tl;
        glm::vec2 tr;
        glm::vec2 br;
        glm::vec2 bl;
    };

    class ColliderComponent : public Component
    {
    private:
        Collider collider;
    public:
        ColliderComponent(GameObject *owner);
        void update_collider();
        Collider& get_collider();
        void normalize_collider();
        ge::Transform create_rendered_collider();
        void update_rendered_collider(ge::Transform *rect);
        bool contains(glm::vec2 pos);
        bool contains(ColliderComponent& other);
        void fit_collider(glm::vec2 factors, glm::vec2 dfactors=glm::vec2(0.5, 0.5));
    };
}

#endif
