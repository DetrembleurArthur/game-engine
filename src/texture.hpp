#ifndef __GE_TEXTURE_HPP__
#define __GE_TEXTURE_HPP__
#include "image.hpp"
#include <glm/glm.hpp>

namespace ge
{
    class Texture
    {
    private:
        unsigned id=0;
    public:
        Texture(Image& image);
        ~Texture();
        void bind() const;
        void unbind() const;
        void active() const;
        void enable_wrap_param(int param);
        void enable_filter_param(int param);
        void enable_linear();
        void enable_nearest();
        void enable_repeat();
        void enable_mirror();
        void enable_clamp_to_edge();
        void enable_clamp_to_border();
        glm::uvec2 get_size() const;
        static Texture *load(const std::string& filename, bool rgb=false);
    };
}

#endif

