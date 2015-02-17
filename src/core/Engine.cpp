#include <wookie/core/Engine.h>
#include <wookie/rendering/GL/GLcontext.h>
#include <wookie/rendering/Camera.h>

void Engine::run()
{
    auto context = glfwGetCurrentContext();
    while (!glfwWindowShouldClose(context)) {
        auto cas = m_world.objectsByComponents<Camera>();
        auto camera = std::get<0>(cas[0]->get<Camera>());
        if (glfwGetKey(context, 'O'))
            camera->offset.x -= 10.0f;
        if (glfwGetKey(context, 'P'))
            camera->offset.x += 10.0f;

        m_world.update();

    }
}

void Engine::setup() {
    m_world.setup();
}

void Engine::shutdown() {
    m_world.shutdown();
}
