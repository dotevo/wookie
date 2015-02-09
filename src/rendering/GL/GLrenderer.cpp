#include <wookie/ecs/GameObject.h>
#include <wookie/rendering/GL/GLrenderer.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void GLrenderer::initialize(std::unique_ptr<Context>&)
{
    m_glShaders.reserve(2);
    m_glShaders.push_back(Shader::createFromFile("../tests/resources/basic_vs.glsl", GL_VERTEX_SHADER));
    m_glShaders.push_back(Shader::createFromFile("../tests/resources/basic_fs.glsl", GL_FRAGMENT_SHADER));

    m_glProgram.reset(new Program{m_glShaders});

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE * sizeof(Vertex), 0, GL_STREAM_DRAW);

    glVertexAttribPointer(AttribLoc::POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(AttribLoc::POSITION);
    glVertexAttribPointer(AttribLoc::TEXTURE, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(AttribLoc::TEXTURE);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, BUFFER_SIZE * sizeof(GLuint), 0, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GLrenderer::render(Renderable const& obj)
{
    glm::mat4 mvp = m_projection * m_view * obj.model;

    GLint unimvp = glGetUniformLocation(m_glProgram->id(), "ie_mvp");
    glUniformMatrix4fv(unimvp, 1, GL_FALSE, glm::value_ptr(mvp));

    glUseProgram(m_glProgram->id());

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, obj.vertices.size() * sizeof(Vertex), &obj.vertices[0]);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, obj.indices.size() * sizeof(GLuint), &obj.indices[0]);

    glDrawElements(GL_TRIANGLES, obj.indices.size(), GL_UNSIGNED_INT, 0);
}
