#include <wookie/core/Engine.h>
#include <wookie/rendering/GL/GLcontext.h>

void Engine::run()
{
    auto context = glfwGetCurrentContext();
    while (!glfwWindowShouldClose(context)) {
        m_world.update();

        glfwPollEvents();
        glfwSwapBuffers(context);
        if (glfwGetKey (context, GLFW_KEY_ESCAPE)) {
          glfwSetWindowShouldClose (context, 1);
        }
    }
}

void Engine::setup() {
    m_world.setup();
}

void Engine::shutdown() {
    m_world.shutdown();
}
