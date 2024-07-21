#ifndef __GE_ANIMATION_COMPONENT_HPP__
#define __GE_ANIMATION_COMPONENT_HPP__
#include <ge/entity/components/component.hpp>
#include <ge/tween/animation.hpp>
#include <vector>
#include <limits>

namespace ge
{
    class AnimationComponent : public UpdatableComponent
    {
    private:
        std::vector<AnimationAbstract *> animations;
        std::vector<AnimationAbstract *> waiting_animations;
        bool animation_required=false;
        bool clean_required=false;
    public:
        using UpdatableComponent::UpdatableComponent;
        virtual ~AnimationComponent();
        virtual void update(float dt) override;
        Animation<float>& to_x(float duration, float to, float from, int period=1, bool backward=false, std::function<float(float)> ftween=ge::tweenf::linear);
        Animation<float>& to_y(float duration, float to, float from, int period=1, bool backward=false, std::function<float(float)> ftween=ge::tweenf::linear);
        Animation<glm::vec2>& to_position(float duration, glm::vec2 to, glm::vec2 from, int period=1, bool backward=false, std::function<float(float)> ftween=ge::tweenf::linear);
        Animation<float>& to_width(float duration, float to, float from, int period=1, bool backward=false, std::function<float(float)> ftween=ge::tweenf::linear);
        Animation<float>& to_height(float duration, float to, float from, int period=1, bool backward=false, std::function<float(float)> ftween=ge::tweenf::linear);
        Animation<glm::vec2>& to_size(float duration, glm::vec2 to, glm::vec2 from, int period=1, bool backward=false, std::function<float(float)> ftween=ge::tweenf::linear);
        Animation<float>& to_rotation(float duration, float to, float from, int period=1, bool backward=false, std::function<float(float)> ftween=ge::tweenf::linear);
        Animation<float>& to_r(float duration, float to, float from, int period=1, bool backward=false, std::function<float(float)> ftween=ge::tweenf::linear);
        Animation<float>& to_g(float duration, float to, float from, int period=1, bool backward=false, std::function<float(float)> ftween=ge::tweenf::linear);
        Animation<float>& to_b(float duration, float to, float from, int period=1, bool backward=false, std::function<float(float)> ftween=ge::tweenf::linear);
        Animation<float>& to_a(float duration, float to, float from, int period=1, bool backward=false, std::function<float(float)> ftween=ge::tweenf::linear);
        Animation<glm::vec4>& to_color(float duration, glm::vec4 to, glm::vec4 from, int period=1, bool backward=false, std::function<float(float)> ftween=ge::tweenf::linear);
    };
}

#endif
