#pragma once

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

enum WindowMode
{
    WINDOWED,
    FULLSCREEN
};

class GLcontext
{
public:
    GLcontext();

    ~GLcontext();

    int width() const;

    int height() const;

    WindowMode mode() const;

    void setTitle(std::string&);

    bool update();

    void initialize();

private:
    static void mouseButtonCallback(GLFWwindow*, int, int, int);
    static void keyCallback(GLFWwindow*, int, int, int, int);
    static void resizeCallback(GLFWwindow*, int, int);
    static void closeCallback(GLFWwindow*);
    static void framebufferSize(GLFWwindow*, int, int);

    GLFWwindow *m_handle {nullptr};
    bool m_resizable {true};
    WindowMode m_mode {WINDOWED};
    std::string m_windowTitle {"myGame"};
    int m_width {1024};
    int m_height {768};
};
