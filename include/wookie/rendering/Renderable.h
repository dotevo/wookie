#pragma once

#include <wookie/ecs/Component.h>
#include <memory>

struct Tile {
    float scale {1.0f};
};

struct Renderable : public Component<Renderable>
{
    Renderable(std::unique_ptr<Tile>&& tile);
    Renderable(const Renderable&);
    Renderable& operator=(Renderable&);

    std::unique_ptr<Tile> m_tile;
};
