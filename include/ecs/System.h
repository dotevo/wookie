#pragma once

#include <cstdint>

class World;

class BaseSystem
{
    friend class World;

public:
    virtual ~BaseSystem() {}

    virtual void setup() = 0;
    virtual void update(World &) = 0;
    virtual void shutdown() = 0;

protected:
    uint32_t m_prio;
};

template <typename T>
class System : public BaseSystem
{
public:
    System(uint32_t prio) {
        m_prio = prio;
    }
};
