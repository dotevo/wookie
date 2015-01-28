#pragma once

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <string>

enum WindowMode
{
    WINDOWED,
    FULLSCREEN
};

class Window
{
public:
    friend class RenderContext;

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    ~Window();

    int width() const;

    int height() const;

    WindowMode mode() const;

    void setTitle(std::string&);

private:
    Window() = default;

    static void mouseButtonCallback(GLFWwindow*, int, int, int);
    static void keyCallback(GLFWwindow*, int, int, int, int);
    static void resizeCallback(GLFWwindow*, int, int);
    static void closeCallback(GLFWwindow*);

    void init(GLFWwindow*);

    bool update();

    GLFWwindow *m_handle {nullptr};
    bool m_resizable {true};
    WindowMode m_mode {WINDOWED};
    std::string m_windowTitle {"myGame"};
    int m_width {1024};
    int m_height {768};
};
