#pragma once

#include <wookie/ecs/System.h>
#include <wookie/rendering/RenderContext.h>
#include <wookie/rendering/Renderer.h>

#include <memory>

class RenderSystem : public System<RenderSystem>
{
public:
    RenderSystem(std::unique_ptr<RenderContext>&& cont,std::unique_ptr<Renderer>&& rend, uint32_t prio) :
        System(prio),
        m_renderer(std::move(rend)),
        m_rc(std::move(cont))
    {}

    virtual void setup() override;
    virtual void update(World &) override;
    virtual void shutdown() override;

private:
    std::unique_ptr<RenderContext> m_rc;
    std::unique_ptr<Renderer> m_renderer;
};
