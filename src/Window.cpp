#include <wookie/Window.h>
#include <wookie/RenderContext.h>

Window::~Window() {
    if (m_handle) {
        glfwSetWindowUserPointer(m_handle, nullptr);
        glfwDestroyWindow(m_handle);
        glfwTerminate();
    }
}

void Window::init(GLFWwindow* handle) {
    m_handle = handle;

    glfwSetKeyCallback(m_handle, keyCallback);
    glfwSetWindowCloseCallback(m_handle, closeCallback);
    glfwSetMouseButtonCallback(m_handle, mouseButtonCallback);
    glfwSetWindowSizeCallback(m_handle, resizeCallback);

    glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

bool Window::update() {
    glfwPollEvents();
    glfwSwapBuffers(m_handle);

    return !glfwWindowShouldClose(m_handle);
}

void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}

void Window::closeCallback(GLFWwindow* window) {
    glfwSetWindowShouldClose(window, GL_TRUE);
}

void Window::resizeCallback(GLFWwindow *window, int width, int height) {
    auto& wnd = static_cast<RenderContext*>(glfwGetWindowUserPointer(window))->window();
    wnd.m_width = width;
    wnd.m_height = height;
    glfwSetWindowSize(window, width, height);
}

WindowMode Window::mode() const {
    if (glfwGetWindowMonitor(m_handle))
        return FULLSCREEN;
    else
        return WINDOWED;
}

void Window::setTitle(std::string &title) {
    glfwSetWindowTitle(m_handle, title.c_str());
}

int Window::width() const {
    return m_width;
}

int Window::height() const {
    return m_height;
}
