#pragma once

#include <glm/glm.hpp>

struct PointLight {
    PointLight(glm::vec3 init_position = {0.f, 0.f, 0.f}, glm::vec3 init_colour = {1.f, 1.f, 1.f})
        : position(init_position)
        , colour(init_colour)
    {
    }
    glm::vec3 position;
    glm::vec3 colour;
};

struct AmbientLight {
    AmbientLight(glm::vec3 init_colour = {.1f, .1f, .1f})
        : colour(init_colour)
    {
    }
    glm::vec3 colour;
};
