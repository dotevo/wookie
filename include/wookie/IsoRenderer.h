#pragma once

#include <wookie/Glutils.h>
#include <wookie/Renderer.h>
#include <wookie/Renderable.h>

#include <memory>
#include <vector>

using namespace glutils;

class IsoRenderer : public Renderer
{
public:
    IsoRenderer();
    virtual ~IsoRenderer() = default;

    template<typename T>
    void loadShaders(T& shader) {
        m_shaderList.push_back(std::move(shader));
    }

    template<typename T, typename... Args>
    void loadShaders(T& shader, Args&... shaders) {
        m_shaderList.push_back(std::move(shader));
        loadShaders(shaders...);
    }

    virtual void render(Renderable&) override;

private:
    std::vector<Shader> m_shaderList;
    std::unique_ptr<Program> m_glProgram {nullptr};

    GLuint m_vao {0};
    GLuint m_vbo {0};
};
