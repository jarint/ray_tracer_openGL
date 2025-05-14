#pragma once

#include <glm/glm.hpp>

struct Intersection {
    Intersection(glm::vec3 init_position = {0.f, 0.f, 0.f}, glm::vec3 init_normal = {0.f, 0.f, -1.f}, float init_distance = 0.f)
        : position(init_position)
        , normal(init_normal)
        , distance(init_distance)
    {
    }
    glm::vec3 position;
    glm::vec3 normal;
    float distance;
};
