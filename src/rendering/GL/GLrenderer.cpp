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

void GLrenderer::render(Renderable const& obj) {
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 trans;
    trans = glm::rotate(trans, 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    GLint unitrans = glGetUniformLocation(m_glProgram->id(), "ie_trans");
    glUniformMatrix4fv(unitrans, 1, GL_TRUE, glm::value_ptr(trans));

    glUseProgram(m_glProgram->id());
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, obj.shape.size() * sizeof(Vertex), &obj.shape[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, obj.indices.size() * sizeof(GLuint), &obj.indices[0]);
    glDrawElements(GL_TRIANGLES, obj.indices.size(), GL_UNSIGNED_INT, 0);
}
