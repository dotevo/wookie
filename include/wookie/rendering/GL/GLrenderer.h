#pragma once

#include <wookie/rendering/GL/Glutils.h>
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

    template<typename T>
    void loadShaders(T& shader) {
        m_shaderList.push_back(std::move(shader));
    }

    template<typename T, typename... Args>
    void loadShaders(T& shader, Args&... shaders) {
        m_shaderList.push_back(std::move(shader));
        loadShaders(shaders...);
    }

    virtual void initialize() override;

    virtual void render(Renderable const&) override;

private:
    std::vector<Shader> m_shaderList;
    std::unique_ptr<Program> m_glProgram {nullptr};

    static constexpr int BUFFER_SIZE = 1000;

    GLuint m_vao {0};
    GLuint m_vbo {0};
    GLuint m_ibo {0};
};
