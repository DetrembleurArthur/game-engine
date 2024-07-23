#ifndef __GE_RENDERER_HPP__
#define __GE_RENDERER_HPP__
#include <ge/graphics/shader.hpp>
#include <ge/graphics/mesh.hpp>
#include <ge/graphics/camera2D.hpp>
#include <ge/entity/transform.hpp>
#include <ge/graphics/texture.hpp>
#include <ge/entity/drawable.hpp>
#include <ge/entity/text.hpp>

namespace ge
{
    class Renderer
    {
    protected:
        Shader *shader;
        Camera2D *camera;
    public:
        Renderer(Shader *shader, Camera2D *camera);
        void begin();
        void end();
        virtual void draw(float dt, Drawable* go) = 0;
        void set_camera(Camera2D *camera);
    };

    class BasicRenderer : public Renderer
    {
    public:
        using Renderer::Renderer;
        virtual void draw(float dt, Drawable *go) override;
    };

    class TexRenderer : public Renderer
    {
    public:
        using Renderer::Renderer;
        virtual void draw(float dt, Drawable *go) override;
    };

    class TextRenderer : public Renderer
    {
    public:
        using Renderer::Renderer;
        virtual void draw(float dt, Drawable *go) override;
    };
}


#endif
