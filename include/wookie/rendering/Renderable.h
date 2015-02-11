#pragma once

#include <wookie/ecs/Component.h>
#include <memory>

struct Tile {
    float gridX {0.0f};
    float gridY {0.0f};
};

struct Renderable : public Component<Renderable>
{
    Renderable(std::unique_ptr<Tile>&& tile);
    Renderable(const Renderable&);
    Renderable& operator=(Renderable&);

    std::unique_ptr<Tile> m_tile;
};
