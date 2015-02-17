#pragma once

#include <wookie/core/WObject.h>
#include <wookie/ecs/World.h>

class Engine: public WObject
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

    void close();

private:
    bool running = true;
    World m_world;
};

inline World& Engine::world() {
    return m_world;
}
