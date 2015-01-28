#include "World.h"

#include <algorithm>

World::World() {
    m_objects.reserve(INITIAL_OBJECTS_VEC_SIZE);
    m_recycled.reserve(INITIAL_OBJECTS_VEC_SIZE);
}

GameObject& World::create()
{
    if (!m_recycled.empty()) {
        auto i = m_recycled.back();
        m_recycled.pop_back();
        auto& obj = m_objects.at(i);
        return obj;
    }

    m_objects.emplace_back();
    auto& obj = m_objects.back();
    obj.index = m_objects.size() - 1;
    return obj;
}

void World::remove(GameObject &go) noexcept {
    go.m_components.clear();
    go.m_componentsFlag.reset();
    m_recycled.emplace_back(go.index);
}

std::vector<GameObject>& World::objects() noexcept {
    return m_objects;
}

GameObject& World::objectsById(uint32_t id) noexcept {
    auto it = std::find_if(std::begin(m_objects),
                           std::end(m_objects),
                           [=](auto const& obj) noexcept { return obj.m_id == id; });

    return *it;
}

void World::setup() {
    for (auto& system : m_systems) {
        system->setup();
    }
}

void World::shutdown() {
    for (auto& system : m_systems) {
        system->shutdown();
    }
}

void World::update() {
    for (auto& system : m_systems) {
        system->update(*this);
    }
}
