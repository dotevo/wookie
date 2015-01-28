#include "Engine.h"
#include "RenderContext.h"


void Engine::run()
{
    auto context = glfwGetCurrentContext();
    auto window = static_cast<RenderContext*>(glfwGetWindowUserPointer(context));

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
