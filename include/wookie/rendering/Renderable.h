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
    Renderable(std::vector<Vertex> vertices, std::vector<GLuint> indices) :
        vertices(std::move(vertices)),
        indices(std::move(indices))
    {}
    // TODO: probably should be enclosed in some kind of Shape/Mesh class
    glm::mat4 model;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
};
