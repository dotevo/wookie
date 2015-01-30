#pragma once

#include <wookie/ecs/Component.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec3 coords;
    glm::vec3 text2d;
};

struct Renderable : public Component<Renderable>
{
    Renderable(std::vector<Vertex> shape)
        : shape(std::move(shape))
    {}

    std::vector<Vertex> shape;
};
