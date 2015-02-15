#pragma once

#include <memory>

struct Renderable;
struct RenderContext;

class Renderer {
public:
    virtual ~Renderer() = default;

    virtual void initialize(std::unique_ptr<RenderContext>&) = 0;
    virtual void render(Renderable const&) = 0;
};
