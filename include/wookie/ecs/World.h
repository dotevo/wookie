#pragma once

#include <wookie/ecs/GameObject.h>
#include <wookie/ecs/System.h>

#include <algorithm>

class World
{
public:
    World();
    ~World() = default;

    World(World const& other) = delete;
    World& operator=(World const& other) = delete;

    World(World&& other) = default;
    World& operator=(World&& other) = default;

    void setup();

    void update();

    void shutdown();

    GameObject& create();

    void remove(GameObject&) noexcept;

    std::vector<GameObject>&
    objects() noexcept;

    std::vector<std::unique_ptr<BaseSystem>>&
    systems() noexcept;

    GameObject& objectsById(uint32_t) noexcept;

    template <typename ...Args>
    auto objectsByComponents();

    template<typename T>
    std::enable_if_t<std::is_base_of<System<T>, T>::value>
    addSystem(std::unique_ptr<T>&& system);

private:
    static constexpr auto INITIAL_OBJECTS_VEC_SIZE = 32;

    std::vector<GameObject> m_objects;
    std::vector<uint32_t> m_recycled;

    std::vector<std::unique_ptr<BaseSystem>> m_systems;
};

template<typename T>
std::enable_if_t<std::is_base_of<System<T>, T>::value>
World::addSystem(std::unique_ptr<T>&& system) {
    m_systems.push_back(std::move(system));
    std::sort(m_systems.begin(), m_systems.end(),
              [](const std::unique_ptr<BaseSystem>& first,
                 const std::unique_ptr<BaseSystem>& second) {
        return first->m_prio < second->m_prio;
    });
}

template <typename ...Args>
auto World::objectsByComponents() {
    std::vector<GameObject*> gobyptr;

    for (auto& obj : m_objects)
        if (obj.hasComponents<Args...>())
            gobyptr.emplace_back(&obj);

    return gobyptr;
}
