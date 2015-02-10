#include <wookie/rendering/Renderable.h>

Renderable::Renderable(std::unique_ptr<Tile>&& tile) :
    m_tile(std::move(tile)) {}


Renderable::Renderable(const Renderable& other) {
    m_tile.reset(new Tile(*other.m_tile));
}

Renderable& Renderable::operator=(Renderable& other) {
    m_tile = std::move(other.m_tile);
    return *this;
}
