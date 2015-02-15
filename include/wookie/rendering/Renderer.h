#pragma once

#include <memory>
#include <wookie/rendering/Context.h>

struct Renderable;

class Renderer {
public:
    virtual ~Renderer() = default;

    virtual void initialize(std::unique_ptr<RenderContext>&) = 0;
    virtual void render(Renderable const&) = 0;
};
