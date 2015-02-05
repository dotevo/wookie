#include <wookie/ecs/GameObject.h>
#include <wookie/rendering/GL/GLrenderer.h>

void GLrenderer::initialize(std::unique_ptr<Context>&) {
    static_assert(sizeof(glm::vec3) == sizeof(GLfloat) * 3, "Platform doesn't support this directly.");

    auto vertex = Shader::createFromFile("../tests/resources/basic_vs.glsl", GL_VERTEX_SHADER);
    auto fragment = Shader::createFromFile("../tests/resources/basic_fs.glsl", GL_FRAGMENT_SHADER);

    m_glProgram.reset(new Program{{vertex, fragment}});

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE * sizeof(Vertex), 0, GL_STREAM_DRAW);

    glVertexAttribPointer(AttribLoc::POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(AttribLoc::POSITION);
    glVertexAttribPointer(AttribLoc::TEXTURE, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(AttribLoc::TEXTURE);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GLrenderer::render(const Renderable& obj) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(m_glProgram->id());
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, obj.shape.size() * sizeof(Vertex), &obj.shape[0]);
    glDrawArrays(GL_TRIANGLES, 0, obj.shape.size());
}
