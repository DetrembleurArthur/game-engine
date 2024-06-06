#ifndef __GE_CAMERA2D_HPP__
#define __GE_CAMERA2D_HPP__
#include <glm/glm.hpp>

namespace ge
{
    struct Ortho
    {
        float left;
        float right;
        float bottom;
        float up;
    };

    class Camera2D
    {
    private:
        glm::mat4 projection;
        glm::mat4 view;
        glm::vec2 position;
        Ortho ortho;
        glm::vec3 zoom;
    public:
        Camera2D();
        Camera2D(const Ortho& ortho);
        ~Camera2D();
        void update_projection();
        void update_view();
        void focus(glm::vec2 focus_position);
        glm::mat4& get_projection();
        glm::mat4& get_view();
        glm::vec2& get_position();
        glm::vec3& get_zoom();
    };
}


#endif
