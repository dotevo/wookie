#pragma once

struct Renderable;

class Renderer {
public:
    virtual ~Renderer() = default;

    virtual void initialize() = 0;
    virtual void render(Renderable const&) = 0;
};
