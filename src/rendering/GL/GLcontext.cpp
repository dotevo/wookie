#include <stdexcept>
#include <iostream>

#include <wookie/rendering/GL/GLcontext.h>

GLcontext::GLcontext() {
    glfwSetErrorCallback([](int code, const char *msg) {
        std::cerr << "glfw error " << code << ": " << msg << std::endl;
    });

    if ( !glfwInit() )
        throw std::runtime_error { "Unable to initialize glfw3 runtime"};

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, m_resizable);

    GLFWmonitor *monitor = nullptr;

    if (m_mode == FULLSCREEN)
        monitor = glfwGetPrimaryMonitor();

    m_handle = glfwCreateWindow(
            m_width,
            m_height,
            m_windowTitle.c_str(),
            monitor,
            nullptr
    );

    if (!m_handle)
        throw std::runtime_error { "Unable to create glfw3 window"};

    glfwSetWindowUserPointer(m_handle, this);
    glfwMakeContextCurrent(m_handle);

    if ( gl3wInit() )
        throw std::runtime_error { "Unable to initialize gl3w"};

    if ( !gl3wIsSupported(3, 2) )
        throw std::runtime_error { "OpenGL 3.2+ not supported "};

    // Initialize window
    initialize();
}

GLcontext::~GLcontext() {
    if (m_handle) {
        glfwSetWindowUserPointer(m_handle, nullptr);
        glfwDestroyWindow(m_handle);
        glfwTerminate();
    }
}

void GLcontext::initialize() {
    glfwSetKeyCallback(m_handle, keyCallback);
    glfwSetWindowCloseCallback(m_handle, closeCallback);
    glfwSetMouseButtonCallback(m_handle, mouseButtonCallback);
    glfwSetWindowSizeCallback(m_handle, resizeCallback);
    glfwSetFramebufferSizeCallback(m_handle, framebufferSize);

    glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

bool GLcontext::update() {
    glfwPollEvents();
    glfwSwapBuffers(m_handle);

    return !glfwWindowShouldClose(m_handle);
}

void GLcontext::framebufferSize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void GLcontext::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

}

void GLcontext::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}

void GLcontext::closeCallback(GLFWwindow* window) {
    glfwSetWindowShouldClose(window, GL_TRUE);
}

void GLcontext::resizeCallback(GLFWwindow *window, int width, int height) {
    glfwSetWindowSize(window, width, height);
}

WindowMode GLcontext::mode() const {
    if (glfwGetWindowMonitor(m_handle))
        return FULLSCREEN;
    else
        return WINDOWED;
}

void GLcontext::setTitle(std::string &title) {
    glfwSetWindowTitle(m_handle, title.c_str());
}

int GLcontext::width() const {
    return m_width;
}

int GLcontext::height() const {
    return m_height;
}
