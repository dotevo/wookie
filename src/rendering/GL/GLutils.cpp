#include <wookie/rendering/GL/Glutils.h>

#include <fstream>
#include <stdexcept>
#include <sstream>

namespace GLutils {

    Shader::Shader(const std::string &source, GLenum shaderType) {
        m_object = glCreateShader(shaderType);
        if (m_object == 0)
            throw std::runtime_error {"Unable to create shader"};

        auto src = source.c_str();
        glShaderSource(m_object, 1, &src, nullptr);
        glCompileShader(m_object);

        GLint status;
        glGetShaderiv(m_object, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(m_object, GL_INFO_LOG_LENGTH, &maxLength);

            //The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(m_object, maxLength, &maxLength, &infoLog[0]);

            std::cerr << &infoLog[0];

            glDeleteShader(m_object);
            m_object = 0;

            throw std::runtime_error {"glCompileShadder failed..."};
        }
    }

    Shader Shader::createFromFile(const std::string &file, GLenum shaderType) {
        std::ifstream f(file.c_str(), std::ios::in | std::ios::binary);
        if (!f.is_open()) {
            throw std::runtime_error {"Cannot open shader definition file: " + file};
        }

        std::ostringstream buffer;
        buffer << f.rdbuf();
        f.close();

        Shader shader(buffer.str(), shaderType);
        return shader;
    }

    Program::Program(const std::vector<Shader>& shaders) {
        if (shaders.size() == 0)
            throw std::runtime_error {"Program cannot be linked with no shaders"};

        m_object = glCreateProgram();
        if (m_object == 0)
            throw std::runtime_error {"glCreateProgram failed"};

        for (auto& shader : shaders) {
            glAttachShader(m_object, shader.id());
        }

        // Bind attributes with predefined names
        glBindAttribLocation(m_object, AttribLoc::POSITION, "ie_pos");
        glBindAttribLocation(m_object, AttribLoc::TEXTURE , "ie_tex");

        glLinkProgram(m_object);

        for (auto& shader : shaders)
            glDetachShader(m_object, shader.id());

        GLint status;
        glGetProgramiv(m_object, GL_LINK_STATUS, &status);
        if (status == GL_FALSE) {
            GLint length;
            glGetProgramiv(m_object, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> log(length);
            glGetProgramInfoLog(m_object, length, &length, &log[0]);
            std::cerr << &log[0];

            glDeleteProgram(m_object);
            m_object = 0;

            throw std::runtime_error {"glLinkProgram failed"};
        }
    }

    Program::~Program() {
        if (m_object != 0)
            glDeleteProgram(m_object);
    }

    GLuint Program::attribIdx(GLchar const *name) {
        GLint attr = glGetAttribLocation(m_object, name);
        if (attr == -1)
            throw std::runtime_error {"attribute not found"};

        return attr;
    }
}
