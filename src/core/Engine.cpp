#include <wookie/core/Engine.h>
#include <wookie/rendering/GL/GLcontext.h>

void Engine::run()
{
    auto context = glfwGetCurrentContext();
    auto window = static_cast<GLcontext*>(glfwGetWindowUserPointer(context));

    while (!glfwWindowShouldClose(context)) {
        m_world.update();
        window->update();
    }
}

void Engine::setup() {
    m_world.setup();
}

void Engine::shutdown() {
    m_world.shutdown();
}
