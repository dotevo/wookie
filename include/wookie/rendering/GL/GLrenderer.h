#pragma once

#include <wookie/rendering/GL/GLutils.h>
#include <wookie/rendering/GL/GLcontext.h>
#include <wookie/rendering/Renderer.h>
#include <wookie/rendering/Renderable.h>

#include <glm/glm.hpp>

#include <memory>
#include <vector>

using namespace GLutils;

class GLrenderer : public Renderer
{
    friend class RenderSystem;
public:
    GLrenderer() = default;
    virtual ~GLrenderer() = default;

    virtual void initialize(std::unique_ptr<Context>&) override;

    virtual void render(Renderable const&) override;

private:
    std::unique_ptr<Program> m_glProgram {nullptr};
    std::vector<std::unique_ptr<Shader>> m_glShaders;

    GLuint m_vao {0};
    GLuint m_vbo {0};
    GLuint m_ebo {0};
    GLuint m_tex {0};

    glm::mat4 m_model;
    glm::mat4 m_view;
    glm::mat4 m_projection;

    std::array<glm::vec3, 8> m_vertices;
    std::array<GLbyte, 6> m_indices;

    float m_scaleFactor {1.0f};
    GLcontext *m_context {nullptr};

    static constexpr int TILE_W = 64;
    static constexpr int TILE_H = 64;
};
