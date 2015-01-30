#include <wookie/rendering/Renderable.h>
#include <wookie/rendering/RenderSystem.h>

#include <wookie/ecs/World.h>

void RenderSystem::setup() {
    m_renderer->initialize();
}

void RenderSystem::shutdown() {
}

void RenderSystem::update(World& world) {
    if (m_renderer == nullptr)
        return;

    for (auto obj : world.objectsByComponents<Renderable>()) {
        const auto r = std::get<0>(obj->get<Renderable>());
        m_renderer->render(*r);
    }
}