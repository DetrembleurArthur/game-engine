#ifndef __GE_TRANSFORM_HPP__
#define __GE_TRANSFORM_HPP__
#include <glm/glm.hpp>

namespace ge
{
    class Transform
    {
    private:
        glm::mat4 model;
        bool dirty=true;
    public:
        glm::vec3 position;
        glm::vec3 size;
        glm::vec3 rotation;
        glm::vec3 origin;
        Transform();
        glm::mat4 get_model();
        void set_size(float width, float height);
        void set_width(float width);
        void set_height(float height);
        glm::vec2 get_size();
        float get_width();
        float get_height();
        void set_position(float x, float y);
        void set_position(glm::vec2 pos);
        void set_x(float x);
        void set_y(float y);
        glm::vec2 get_position();
        float get_x();
        float get_y();
        void set_origin(float x, float y);
        void set_tl_origin();
        void set_tr_origin();
        void set_br_origin();
        void set_bl_origin();
        void set_center_origin();
        void set_origin_position(glm::vec2 origin, glm::vec2 position);
        glm::vec2 get_origin_position(glm::vec2 origin);
        glm::vec2 get_tl_position();
        glm::vec2 get_tr_position();
        glm::vec2 get_bl_position();
        glm::vec2 get_br_position();
        glm::vec2 get_center_position();
        void set_tl_position(glm::vec2 position);
        void set_tr_position(glm::vec2 position);
        void set_bl_position(glm::vec2 position);
        void set_br_position(glm::vec2 position);
        void set_center_position(glm::vec2 position);
        float get_angle(glm::vec2 target);
        float get_rotation();
        glm::vec2 get_direction(glm::vec2 target);
        void set_rotation(float angle);
        void set_relative_angle(glm::vec2 target, float angle);
        void set_relative_angle(glm::vec2 target, float angle, float distance);
        void set_angle(glm::vec2 target, float angle, float distance);
        float get_distance(glm::vec2 target);
        void set_dirty(bool value=true);
        bool is_dirty() const;
        bool contains(glm::vec2 point);
        glm::vec2 get_origin();
    };
}


#endif

