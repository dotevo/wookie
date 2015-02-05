#pragma once

#include <wookie/rendering/GL/GLutils.h>
#include <wookie/rendering/Renderer.h>
#include <wookie/rendering/Renderable.h>

#include <memory>
#include <vector>

using namespace GLutils;

class GLrenderer : public Renderer
{
public:
    GLrenderer() = default;
    virtual ~GLrenderer() = default;

    virtual void initialize() override;

    virtual void render(Renderable const&) override;

private:
    std::unique_ptr<Program> m_glProgram {nullptr};

    static constexpr int BUFFER_SIZE = 1000;

    GLuint m_vao {0};
    GLuint m_vbo {0};
    GLuint m_ebo {0};
};
