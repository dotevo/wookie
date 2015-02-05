#pragma once

#include <wookie/ecs/Component.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
};

struct Renderable : public Component<Renderable>
{
    Renderable(std::vector<Vertex> shape)
        : shape(std::move(shape))
    {}

    std::vector<Vertex> shape;
};
