#pragma once

#include <bitset>

struct BaseComponent
{
    static uint32_t m_id;
    virtual ~BaseComponent() = default;
};

template<class T>
struct Component : public BaseComponent
{
    static auto group() {
        static std::bitset<MAX_COMPONENTS> m_bit = 1 << m_id++;
        return m_bit;
    }

private:
    constexpr static uint32_t MAX_COMPONENTS = 32;
};
