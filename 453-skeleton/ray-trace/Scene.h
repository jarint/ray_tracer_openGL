#pragma once

#include "Lights.h"
#include "Object.h"
#include "Ray.h"

struct TraceParameters {
    int self_object_index = -1;  // May be useful for self intersections
    int level             = 0;
};
struct TraceResult {
    glm::vec3 colour = {0.f, 0.f, 0.f};
    double depth     = 0.f;
};

struct IntersectionParameters {
    int self_object_index = -1;  // May be useful for self intersections
    float self_eps        = 0.001f;  // May be useful for self intersections
};

struct IntersectionResult {
    Intersection intersection;
    size_t object_index;
};

struct Scene {
    glm::vec3 sky_colour;  // Used for when the ray goes into the sky
    AmbientLight ambient_light;  // Ambient lighing colour
    PointLight point_light;  // More lights?
    std::vector<Object> objects;

    TraceResult trace(const Ray &ray, TraceParameters params = TraceParameters());

    // Procedure to calculate which object it hits
    std::optional<IntersectionResult>
    closestIntersection(const Ray &ray, IntersectionParameters params = IntersectionParameters());
};
