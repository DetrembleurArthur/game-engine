#ifndef __GE_IMAGE_HPP__
#define __GE_IMAGE_HPP__
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ge/utils/log.hpp>

namespace ge
{
    class Image
    {
    private:
        std::string filename;
        GLFWimage image;
        int channels=0;
    public:
        Image(const std::string& filename, bool load=false);
        ~Image();
        void load(int target_channels=0);
        void unload();
        GLFWimage& get();
        int get_channels() const;
    };
}

#endif
