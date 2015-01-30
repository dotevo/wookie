#pragma once

#include <wookie/core/RenderContext.h>
#include <wookie/ecs/System.h>
#include <wookie/rendering/Renderer.h>

#include <memory>

class RenderSystem : public System<RenderSystem>
{
public:
    RenderSystem(std::unique_ptr<Renderer>&& rend, uint32_t prio) :
        System(prio),
        m_renderer(std::move(rend))
    {}

    virtual void setup() override;
    virtual void update(World &) override;
    virtual void shutdown() override;

private:
    RenderContext m_rc;
    std::unique_ptr<Renderer> m_renderer;
};
