#include <stdexcept>
#include <iostream>

#include "RenderContext.h"

RenderContext::RenderContext() {
    glfwSetErrorCallback([](int code, const char *msg) {
        std::cerr << "glfw error " << code << ": " << msg << std::endl;
    });

    if ( !glfwInit() )
        throw std::runtime_error { "Unable to initialize glfw3 runtime"};

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, m_window.m_resizable);

    GLFWmonitor *monitor = nullptr;

    if (m_window.m_mode == FULLSCREEN)
        monitor = glfwGetPrimaryMonitor();

    auto wnd_handle = glfwCreateWindow(
            m_window.m_width,
            m_window.m_height,
            m_window.m_windowTitle.c_str(),
            monitor,
            nullptr
    );

    if (!wnd_handle)
        throw std::runtime_error { "Unable to create glfw3 window"};

    glfwSetWindowUserPointer(wnd_handle, this);
    glfwMakeContextCurrent(wnd_handle);

    if ( gl3wInit() )
        throw std::runtime_error { "Unable to initialize gl3w"};

    if ( !gl3wIsSupported(3, 2) )
        throw std::runtime_error { "OpenGL 3.2+ not supported "};

    m_window.init(wnd_handle);
}

Window& RenderContext::window() {
    return m_window;
}

bool RenderContext::update() {
    return m_window.update();
}
