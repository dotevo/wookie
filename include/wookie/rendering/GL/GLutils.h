#pragma once

#include <GL/gl3w.h>

#include <string>
#include <vector>
#include <iostream>

namespace GLutils {

    enum AttribLoc { POSITION, TEXTURE };

    class Shader {
    public:
        Shader(const std::string &shaderSource, GLenum shaderType);
        ~Shader() = default;

        static Shader createFromFile(const std::string& file, GLenum shaderType);

        GLuint id() const {
            return m_object;
        }

        Shader(const Shader& rhs) = default;
        Shader& operator=(const Shader& rhs) = default;

    private:
        GLuint m_object {0};
    };

    class Program {
    public:
        Program(const std::vector<Shader>& shaders);
        ~Program();

        GLuint id() const {
            return m_object;
        }

        GLuint attribIdx(const GLchar*);

        Program(const Program&) = delete;
        Program& operator=(const Program&) = delete;

    private:
        GLuint m_object {0};

    };
}
