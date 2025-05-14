#pragma once
#include <glm/glm.hpp>

struct Ray {
    Ray(glm::vec3 init_origin = {0.f, 0.f, 0.f}, glm::vec3 init_direction = {0.f, 0.f, -1.f})
        : origin(init_origin)
        , direction(init_direction)
    {
    }

    Ray normalize() const { return Ray(origin, glm::normalize(direction)); }

    glm::vec3 origin;
    glm::vec3 direction;
};
