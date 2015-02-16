#include <wookie/rendering/GL/GLTileRenderer.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void GLTileRenderer::initialize(std::unique_ptr<RenderContext>& rc)
{
    m_context = static_cast<GLcontext*>(rc.get());

    m_glShaders.reserve(2);
    m_glShaders.push_back(Shader::createFromFile("../tests/resources/basic_vs.glsl", GL_VERTEX_SHADER));
    m_glShaders.push_back(Shader::createFromFile("../tests/resources/basic_fs.glsl", GL_FRAGMENT_SHADER));

    m_glProgram.reset(new Program{m_glShaders});

    // Everything is a square
    m_vertices = {{
        {-0.5f, 0.5f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {-0.5f, -0.5f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.5f, -0.5f, 0.0f},
        {1.0f, 1.0f, 0.0f},
        {0.5f, 0.5f, 0.0f},
        {1.0f, 0.0f, 0.0f},
    }};

    m_indices = {0, 1, 2, 0, 2, 3};

    // Camera is fixed so we set it once
    glm::vec3 eye = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 center = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    m_view = glm::lookAt(eye, center, up);

    // Projection matrix also fixed
    m_projection = glm::ortho(-(float)m_context->m_fbWidth/2, (float)m_context->m_fbWidth/2,
                              -(float)m_context->m_fbHeight/2, (float)m_context->m_fbHeight/2,
                              0.0f, -10.0f);

    // OpenGL specific stuff
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);;

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);
    glGenTextures(1, &m_tex);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(AttribLoc::POSITION, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), 0);
    glEnableVertexAttribArray(AttribLoc::POSITION);

    glVertexAttribPointer(AttribLoc::TEXTURE, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void*)sizeof(glm::vec3));
    glEnableVertexAttribArray(AttribLoc::TEXTURE);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLbyte), &m_indices[0], GL_STATIC_DRAW);

    glBindTexture(GL_TEXTURE_2D, m_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TILE_W, TILE_H, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_TEXTURE_2D, 0);
}

void GLTileRenderer::render(Renderable const& obj)
{
    m_model = glm::mat4();

    auto scaleX = m_scaleFactor * TILE_W;
    auto scaleY = m_scaleFactor * TILE_H;
    auto scaleMat = glm::scale(glm::mat4(1.0f),glm::vec3(scaleX, scaleY, 1.0f));

    auto translateX = obj.gridY * TILE_W/2 + obj.gridX * TILE_W/2;
    auto translateY = obj.gridY * TILE_H/4 - obj.gridX * TILE_H/4;
    auto translateMat = glm::translate(glm::mat4(1.0f), glm::vec3(translateX, translateY, 0.0f));

    m_model = translateMat * scaleMat;

    glm::mat4 mvp = m_projection * m_view * m_model;

    GLint unimvp = glGetUniformLocation(m_glProgram->id(), "ie_mvp");
    glUniformMatrix4fv(unimvp, 1, GL_FALSE, glm::value_ptr(mvp));

    glUseProgram(m_glProgram->id());

    glBindVertexArray(m_vao);

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, TILE_W, TILE_H, GL_RGBA, GL_UNSIGNED_BYTE, obj.img->data());

    glUniform1i(glGetUniformLocation(m_glProgram->id(), "ie_sampler2D"), 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
}
