#pragma once

#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec2 uv;

    Vertex()
    {
        position = glm::vec3(0.0f);
        uv       = glm::vec2(0.0f);
    };
};
