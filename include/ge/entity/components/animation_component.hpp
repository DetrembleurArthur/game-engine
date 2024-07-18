#ifndef __GE_ANIMATION_COMPONENT_HPP__
#define __GE_ANIMATION_COMPONENT_HPP__
#include <ge/entity/components/component.hpp>
#include <ge/tween/animation.hpp>
#include <vector>

namespace ge
{
    class AnimationComponent : public UpdatableComponent
    {
    private:
        std::vector<Animation *> animations;
        std::vector<Animation *> waiting_animations;
        bool animation_required=false;
        bool clean_required=false;
    public:
        using UpdatableComponent::UpdatableComponent;
        virtual ~AnimationComponent();
        virtual void update(float dt) override;
        Animation& create(float duration, FloatProperty *target, int period=0, bool backward=false);
    };
}

#endif
