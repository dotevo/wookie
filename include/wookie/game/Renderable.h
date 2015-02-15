#pragma once

#include <memory>

#include <wookie/ecs/Component.h>
#include <wookie/game/Tile.h>

struct Renderable : public Component<Renderable>
{
    Renderable(std::unique_ptr<Tile>&& tile);
    Renderable(const Renderable&);
    Renderable& operator=(Renderable&);

    std::unique_ptr<Tile> m_tile;
};
