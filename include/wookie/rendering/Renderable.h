#pragma once

#include <wookie/ecs/Component.h>
#include <wookie/resource/Image.h>

#include <memory>

struct Tile {
    Tile(int X, int Y) : gridX(X), gridY(Y), img("tile.png") {}

    int gridX;
    int gridY;
    Image img;
};

struct Renderable : public Component<Renderable>
{
    Renderable(std::unique_ptr<Tile>&& tile);
    Renderable(const Renderable&);
    Renderable& operator=(Renderable&);

    std::unique_ptr<Tile> m_tile;
};
