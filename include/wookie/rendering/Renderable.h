#pragma once

#include <wookie/ecs/Component.h>
#include <memory>

struct Tile {
    Tile(int X, int Y) : gridX(X), gridY(Y) {}

    int gridX;
    int gridY;
};

struct Renderable : public Component<Renderable>
{
    Renderable(std::unique_ptr<Tile>&& tile);
    Renderable(const Renderable&);
    Renderable& operator=(Renderable&);

    std::unique_ptr<Tile> m_tile;
};
