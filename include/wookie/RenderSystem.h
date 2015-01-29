#pragma once

#include <wookie/RenderContext.h>
#include <wookie/Renderer.h>

#include <wookie/ecs/System.h>
#include <memory>

class RenderSystem : public System<RenderSystem>
{
public:
    RenderSystem(uint32_t prio) : System(prio) {}

    virtual void setup() override;
    virtual void update(World &) override;
    virtual void shutdown() override;

private:
    RenderContext m_rc;
    std::unique_ptr<Renderer> m_renderer;
};
