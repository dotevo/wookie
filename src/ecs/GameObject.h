#pragma once

#include "Component.h"

#include <bitset>
#include <unordered_map>
#include <memory>
#include <vector>

class GameObject
{
    friend class World;

public:
    GameObject() {
        static uint32_t id = 0;
        m_id = id++;
    }

    ~GameObject() = default;

    GameObject(GameObject&&) = default;

    GameObject& operator=(GameObject&&) = default;

    template <typename T>
    std::enable_if_t <std::is_base_of<Component<T>, T>::value, bool>
    hasComponents();

    template <typename T, typename U, typename ...Args>
    std::enable_if_t <std::is_base_of<Component<T>, T>::value, bool>
    hasComponents();

    //TODO: some kind of SFINAE needed here
    template<typename T>
    auto get();

    template <typename T, typename U, typename... Args>
    auto get();

    template <typename T, typename ...Args>
    std::enable_if_t <std::is_base_of<Component<T>, T>::value>
    add(T &c, Args& ...args);

    void add() {}

    template <typename T>
    std::enable_if_t <std::is_base_of<Component<T>, T>::value>
    remove();

    template <typename T, typename U, typename ...Args>
    std::enable_if_t <std::is_base_of<Component<T>, T>::value>
    remove();

private:
    uint32_t m_id {0};
    size_t index {0};

    std::bitset<32> m_componentsFlag;
    std::unordered_map<unsigned long, std::shared_ptr<BaseComponent> > m_components;
};

template <typename T>
std::enable_if_t <std::is_base_of<Component<T>, T>::value, bool>
GameObject::hasComponents() {
    const auto component_group = T::group();
    return (component_group & m_componentsFlag).any();
}

template <typename T, typename U, typename ...Args>
std::enable_if_t<std::is_base_of<Component<T>, T>::value, bool>
GameObject::hasComponents() {
    return hasComponents<T>() && hasComponents <U, Args...>();
}

template<typename T>
auto GameObject::get() {
    const auto component_group = T::group();
    auto val = std::static_pointer_cast<T>(m_components[component_group.to_ulong()]);
    return std::make_tuple(val);
}

template <typename T, typename U, typename... Args>
auto GameObject::get() {
    return std::tuple_cat(get<T>(), get<U, Args...>());
}

template <typename T, typename ...Args>
std::enable_if_t <std::is_base_of<Component<T>, T>::value>
GameObject::add(T &c, Args& ...args) {
    const auto component_group = T::group();
    m_componentsFlag |= component_group;
    m_components[component_group.to_ulong()] = std::make_shared<T>(c);
    add(args...);
}

template <typename T>
std::enable_if_t <std::is_base_of<Component<T>, T>::value>
GameObject::remove() {
    const auto component_group = T::group();
    m_componentsFlag &= ~component_group;
    m_components.erase(component_group.to_ulong());
}

template <typename T, typename U, typename ...Args>
std::enable_if_t <std::is_base_of<Component<T>, T>::value>
GameObject::remove() {
    const auto component_group = T::group();
    m_componentsFlag &= ~component_group;
    m_components.erase(component_group.to_ulong());
    remove<U, Args...>();
}
