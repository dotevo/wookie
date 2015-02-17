#include <wookie/core/Engine.h>
#include <wookie/rendering/GL/GLcontext.h>
#include <wookie/rendering/Camera.h>

void Engine::run()
{
    while (running) {
        m_world.update();
    }
}

void Engine::setup() {
    m_world.setup();
}

void Engine::shutdown() {
    m_world.shutdown();
}

void Engine::close(){
    running = false;
}
