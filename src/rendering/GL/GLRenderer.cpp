#include <wookie/ecs/GameObject.h>
#include <wookie/rendering/GL/GLrenderer.h>

void GLrenderer::initialize() {
    auto vertex = Shader::createFromFile("../tests/resources/basic_vs.glsl", GL_VERTEX_SHADER);
    auto fragment = Shader::createFromFile("../tests/resources/basic_fs.glsl", GL_FRAGMENT_SHADER);

    loadShaders(vertex, fragment);
    m_glProgram = std::make_unique<Program>(m_shaderList);

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glVertexAttribPointer(AttribLoc::POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, coords));
    glEnableVertexAttribArray(AttribLoc::POSITION);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLrenderer::render(const Renderable& obj) {

    static_assert(sizeof(glm::vec3) == sizeof(GLfloat) * 3, "Platform doesn't support this directly.");

    glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(GL_ARRAY_BUFFER, obj.shape.size() * sizeof(Vertex), &obj.shape[0], GL_STREAM_DRAW);

    glUseProgram(m_glProgram->id());
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glUseProgram(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}