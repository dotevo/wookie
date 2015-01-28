#include "Renderable.h"
#include "RenderSystem.h"
#include "IsoRenderer.h"

#include <World.h>

void RenderSystem::setup() {
    m_renderer = std::make_unique<IsoRenderer>();
}

void RenderSystem::shutdown() {
}

void RenderSystem::update(World& world) {
    for (auto obj : world.objectsByComponents<Renderable>()) {
        auto r = std::get<0>(obj->get<Renderable>());
        m_renderer->render(*r);
    }
}
