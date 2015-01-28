#pragma once

struct Renderable;

class Renderer {
public:
    virtual ~Renderer() = default;

    virtual void render(Renderable&) = 0;
};
