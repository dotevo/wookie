#pragma once

#include <wookie/ecs/World.h>

class Engine
{
public:
    Engine() = default;
    ~Engine() = default;

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    World& world();

    void setup();
    void run();
    void shutdown();

private:
    World m_world;
};

inline World& Engine::world() {
    return m_world;
}
