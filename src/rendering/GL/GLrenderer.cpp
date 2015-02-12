#include <wookie/ecs/GameObject.h>
#include <wookie/rendering/GL/GLrenderer.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

void GLrenderer::initialize(std::unique_ptr<Context>& rc)
{
    m_context = static_cast<GLcontext*>(rc.get());

    m_glShaders.reserve(2);
    m_glShaders.push_back(Shader::createFromFile("../tests/resources/basic_vs.glsl", GL_VERTEX_SHADER));
    m_glShaders.push_back(Shader::createFromFile("../tests/resources/basic_fs.glsl", GL_FRAGMENT_SHADER));

    m_glProgram.reset(new Program{m_glShaders});

    // Everything is a square
    m_vertices = {{
        {-0.5f, 0.5f, 0.0f},
        {1.0f, 0.0f, 0.0f},
        {-0.5f, -0.5f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.5f, -0.5f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {0.5f, 0.5f, 0.0f},
        {1.0f, 1.0f, 1.0f},
    }};

    m_indices = {0, 3, 2, 0, 2, 1};

    // Camera is fixed so we set it once
    glm::vec3 eye = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 center = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    m_view = glm::lookAt(eye, center, up);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(AttribLoc::POSITION, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);
    glEnableVertexAttribArray(AttribLoc::POSITION);

    glVertexAttribPointer(AttribLoc::TEXTURE, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void*)sizeof(glm::vec3));
    glEnableVertexAttribArray(AttribLoc::TEXTURE);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLbyte), &m_indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLrenderer::render(Renderable const& obj)
{
    m_model = m_projection = glm::mat4();

    auto scaleX = m_scaleFactor * 64;
    auto scaleY = m_scaleFactor * 64;
    auto scaleMat = glm::scale(glm::mat4(1.0f),glm::vec3(scaleX, scaleY, 1.0f));

    auto translateX = -obj.m_tile->gridX * 64;
    auto translateY = -obj.m_tile->gridY * 64;
    auto translateMat = glm::translate(glm::mat4(1.0f), glm::vec3(translateX, translateY, 0.0f));

    m_model = translateMat * scaleMat;

    m_projection = glm::ortho(-(float)m_context->m_fbWidth/2, (float)m_context->m_fbWidth/2,
                              -(float)m_context->m_fbHeight/2, (float)m_context->m_fbHeight/2, 0.0f, 10.0f);

    glm::mat4 mvp = m_projection * m_view * m_model;

    GLint unimvp = glGetUniformLocation(m_glProgram->id(), "ie_mvp");
    glUniformMatrix4fv(unimvp, 1, GL_FALSE, glm::value_ptr(mvp));

    glUseProgram(m_glProgram->id());

    glBindVertexArray(m_vao);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
}
