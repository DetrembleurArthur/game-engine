#ifndef __GE_MOVE_COMPONENT_HPP__
#define __GE_MOVE_COMPONENT_HPP__
#include <ge/entity/components/component.hpp>
#include <glm/glm.hpp>
#include <limits>

namespace ge
{
    class MoveComponent : public UpdatableComponent
    {
    public:
        glm::vec2 speed = {0, 0};
        glm::vec2 accel = {0, 0};
        glm::vec2 limit = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
        float rotation_speed = 0;
        float rotation_accel = 0;
        float rotation_limit = std::numeric_limits<float>::max();
        glm::vec2 angle_target = {0, 0};
        float angle_distance = 0;
        float angle_accumulator = 0;
        float angle_speed = 0;
        float angle_accel = 0;
        float angle_limit = std::numeric_limits<float>::max();
        using UpdatableComponent::UpdatableComponent;
        virtual void update(float dt) override;
        void toward(glm::vec2 target, glm::vec2 speed={1, 1});
        void toward_accel(glm::vec2 target, glm::vec2 accel={1, 1});
        void around(glm::vec2 target, float distance=0);
    };
}


#endif

