#include "ge/graphics/shader.hpp"
#include <ge/utils/log.hpp>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

ge::Shader *ge::Shader::BASIC = nullptr;
ge::Shader *ge::Shader::TEX = nullptr;
ge::Shader *ge::Shader::TEXT = nullptr;

void ge::Shader::load_default_shaders()
{
    ge::Shader::BASIC = new Shader();
    ge::Shader::BASIC->load_from_file("./res/shaders/basic/vertex.glsl", "./res/shaders/basic/fragment.glsl");
    ge::Shader::TEX = new Shader();
    ge::Shader::TEX->load_from_file("./res/shaders/tex/vertex.glsl", "./res/shaders/tex/fragment.glsl");
    ge::Shader::TEXT = new Shader();
    ge::Shader::TEXT->load_from_file("./res/shaders/text/vertex.glsl", "./res/shaders/text/fragment.glsl");
}

void ge::Shader::unload_default_shaders()
{
    if(ge::Shader::BASIC)
    {
        delete ge::Shader::BASIC;
        ge::Shader::BASIC = nullptr;
    }
    if(ge::Shader::TEX)
    {
        delete ge::Shader::TEX;
        ge::Shader::TEX = nullptr;
    }
    if(ge::Shader::TEXT)
    {
        delete ge::Shader::TEXT;
        ge::Shader::TEXT = nullptr;
    }
}

ge::Shader::Shader()
{
}

ge::Shader::~Shader()
{
    if(vertex_shader && fragment_shader && program)
        destroy();
}

void ge::Shader::destroy()
{
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    glDeleteShader(program);
    vertex_shader = 0;
    fragment_shader = 0;
    program = 0;
    log("shader destroyed", LogLevels::SHADER);
}

void ge::Shader::load(const std::string &vsource, const std::string &fsource)
{
    if(vertex_shader && fragment_shader && program)
        destroy();
    
    int success;
    char info_log[512];
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *vertex_source = vsource.c_str();
    const char *fragment_source = fsource.c_str();
    
    glShaderSource(vertex_shader, 1, &vertex_source, nullptr);
    glShaderSource(fragment_shader, 1, &fragment_source, nullptr);
    glCompileShader(vertex_shader);
    glCompileShader(fragment_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
        log("vertex shader: " + std::string(info_log), LogLevels::ERROR);
    }
    else
    {
        log("vertex shader compiled succesfuly", LogLevels::SHADER);
    }
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
        log("fragment shader: " + std::string(info_log), LogLevels::ERROR);
    }
    else
    {
        log("fragment shader compiled succesfuly", LogLevels::SHADER);
    }
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(program, 512, NULL, info_log);
        log("shader program can not be linked with shaders", LogLevels::ERROR);
    }
    else
    {
        log("shader linked succesfuly", LogLevels::SHADER);
    }
}

void ge::Shader::load_from_file(const std::string &vfilename, const std::string& ffilename)
{
    std::stringstream buffer;
    std::string vsource, fsource;
    std::ifstream file;
    file.open(vfilename);
    if(file.is_open())
    {
        buffer << file.rdbuf();
        vsource = buffer.str();
        log(vfilename + " vertex shader source extracted successfuly", LogLevels::SHADER);
    }
    else
    {
        log(vfilename + " vertex shader source not extracted", LogLevels::ERROR);
    }
    file.close();
    buffer = std::stringstream();
    file.open(ffilename);
    if(file.is_open())
    {
        buffer << file.rdbuf();
        fsource = buffer.str();
        log(ffilename + " fragment shader source extracted successfuly", LogLevels::SHADER);
    }
    else
    {
        log(ffilename + " fragment shader source not extracted", LogLevels::ERROR);
    }
    file.close();
    if(!vsource.empty() && !fsource.empty())
        load(vsource, fsource);
}

void ge::Shader::use()
{
    glUseProgram(program);
}

void ge::Shader::unuse()
{
    glUseProgram(0);
}

void ge::Shader::set_uniform_color(const glm::vec4 &color, const std::string &var_name)
{
    int loc = glGetUniformLocation(program, var_name.c_str());
    glUniform4fv(loc, 1, &color[0]);
}

void ge::Shader::set_uniform_model(const glm::mat4 &model, const std::string &var_name)
{
    int loc = glGetUniformLocation(program, var_name.c_str());
    glUniformMatrix4fv(loc, 1, false, glm::value_ptr(model));
}

void ge::Shader::set_uniform_view(const glm::mat4 &view, const std::string &var_name)
{
    int loc = glGetUniformLocation(program, var_name.c_str());
    glUniformMatrix4fv(loc, 1, false, glm::value_ptr(view));
}

void ge::Shader::set_uniform_projection(const glm::mat4 &projection, const std::string &var_name)
{
    int loc = glGetUniformLocation(program, var_name.c_str());
    glUniformMatrix4fv(loc, 1, false, glm::value_ptr(projection));
}

void ge::Shader::set_uniform_enable_texture(int value, const std::string &var_name)
{
    int loc = glGetUniformLocation(program, var_name.c_str());
    glUniform1i(loc, value);
}

void ge::Shader::set_uniform_texture(int value, const std::string &var_name)
{
    int loc = glGetUniformLocation(program, var_name.c_str());
    glUniform1i(loc, value);
}
