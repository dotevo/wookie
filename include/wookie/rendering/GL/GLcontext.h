#pragma once

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <wookie/rendering/Context.h>

class GLcontext: public Context
{
public:
    GLcontext();

    ~GLcontext();

    virtual int width() const override;

    virtual int height() const override;

    virtual WindowMode mode() const override;

    virtual void setWindowTitle(std::string&) override;

    virtual void update() override;

    virtual void clear() override;

private:
    static void mouseButtonCallback(GLFWwindow*, int, int, int);
    static void keyCallback(GLFWwindow*, int, int, int, int);
    static void resizeCallback(GLFWwindow*, int, int);
    static void closeCallback(GLFWwindow*);
    static void framebufferSize(GLFWwindow*, int, int);

    void windowSetup();

    GLFWwindow *m_handle {nullptr};
    bool m_resizable {true};
    WindowMode m_mode {WINDOWED};
    std::string m_windowTitle {"myGame"};
    int m_width {1024};
    int m_height {768};
};
