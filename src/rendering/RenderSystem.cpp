#include <wookie/rendering/RenderSystem.h>
#include <wookie/rendering/Camera.h>
#include <wookie/ecs/World.h>
#include <wookie/game/isometric/Renderable.h>

void RenderSystem::setup() {
    m_renderer->initialize(m_rc);
}

void RenderSystem::shutdown() {
}

void RenderSystem::update(World& world)
{
    if (m_renderer == nullptr)
        return;

    m_rc->clear();

    for (auto cameras : world.objectsByComponents<Camera>()) {
        auto camera = std::get<0>(cameras->get<Camera>());
        if (camera->active) {
            for (auto obj : world.objectsByComponents<Renderable>()) {
                auto r = std::get<0>(obj->get<Renderable>());
                m_renderer->render(*r, *camera);
            }
        }
    }

    m_rc->update();
}
