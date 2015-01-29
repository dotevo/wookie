#pragma once

#include <wookie/ecs/Component.h>
#include <glm/glm.hpp>
#include <vector>

struct Renderable : public Component<Renderable>
{
    Renderable(std::vector<glm::vec3> v)
        : vertices(std::move(v)) {}

    std::vector<glm::vec3> vertices;
};
