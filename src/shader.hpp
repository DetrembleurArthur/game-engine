#ifndef __GE_SHADER_HPP__
#define __GE_SHADER_HPP__
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

namespace ge
{
    class Shader
    {
    private:
        unsigned vertex_shader=0;
        unsigned fragment_shader=0;
        unsigned program=0;
    public:
        static Shader *DEFAULT;
        static void load_default_shaders();
        static void unload_default_shaders();
        Shader();
        ~Shader();
        void destroy();
        void load(const std::string& vsource, const std::string& fsource);
        void load_from_file(const std::string& vfilename, const std::string& ffilename);
        void use();
        void unuse();
        void set_uniform_color(const glm::vec4& color, const std::string& var_name="uColor");
    };
}


#endif

