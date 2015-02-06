#pragma once

#include <wookie/ecs/Component.h>
#include <GL/gl3w.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
};

struct Renderable : public Component<Renderable>
{
    Renderable(std::vector<Vertex> shape, std::vector<GLuint> indices) :
        shape(std::move(shape)),
        indices(std::move(indices))
    {}

    std::vector<Vertex> shape;
    std::vector<GLuint> indices;
};
