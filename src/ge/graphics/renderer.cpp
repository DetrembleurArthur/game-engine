#include "ge/graphics/renderer.hpp"
#include <ge/entity/text.hpp>

ge::Renderer::Renderer(Shader *shader, Camera2D *camera) : shader(shader), camera(camera)
{
}

void ge::Renderer::begin()
{
    shader->use();
}

void ge::Renderer::end()
{
    shader->unuse();
}

/*
float ge::Mesh::RECT_TEX_VERTICES[20] = {
        0, 0, 0, 0, 0,
        0, 1, 0, 0, 1,
        1, 1, 0, 1, 1,
        1, 0, 0, 1, 0
};*/
void ge::Renderer::draw(float dt, GameObject* go)
{
    shader->set_uniform_color(go->get_color());
    shader->set_uniform_model(go->get_transform().get_model());
    Mesh *mesh = go->get_mesh();
    if(camera)
    {
        camera->update_projection();
        camera->update_view();
        shader->set_uniform_view(camera->get_view());
        shader->set_uniform_projection(camera->get_projection());
        if(mesh)
        {
            if(dynamic_cast<Text *>(go))
            {
                Text *text_object = dynamic_cast<Text *>(go);
                std::string&& text = text_object->get_text();
                Font *font = text_object->get_font();
                float x = 0, y = 0, scale = 1;
                for(auto it = text.begin(); it != text.end(); it++)
                {
                    char c = *it;
                    Glyph& glyph = font->get_glyphs()[c];
                    float xpos = x + glyph.bearing.x * scale;
                    float ypos = y - glyph.bearing.y * scale;

                    float w = glyph.size.x * scale;
                    float h = glyph.size.y * scale;
                    float vertices[4][5] = {
                        { xpos,     ypos, 0,  0.0f, 0.0f },            
                        { xpos,     ypos+h  , 0,    0.0f, 1.0f },
                        { xpos + w, ypos+h,   0,    1.0f, 1.0f },
                        { xpos + w, ypos,    0,   1.0f, 0.0f },   
                    };
                    Texture& texture = *glyph.texture;
                    shader->set_uniform_enable_texture(2);
                    texture.active();
                    texture.bind();
                    mesh->update(vertices, sizeof(vertices));
                    shader->set_uniform_texture();
                    mesh->draw();
                    texture.unbind();
                    x += (glyph.advance >> 6) * scale;
                }
                return;
            }
            else
            {
                const Texture *texture = go->get_texture();
                shader->set_uniform_enable_texture(texture && mesh->is_textured());
                if(texture)
                {
                    texture->active();
                    texture->bind();
                    shader->set_uniform_texture();
                }
            }
        }
    }
    if(mesh)
        mesh->draw();
}

void ge::Renderer::set_camera(Camera2D *camera)
{
    this->camera = camera;
}
