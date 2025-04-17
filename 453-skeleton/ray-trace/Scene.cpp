#include <algorithm>

#include "Scene.h"

#include "../Log.h"

TraceResult Scene::trace(const Ray &ray, TraceParameters params)
{
    TraceResult result;
    result.colour = sky_colour;

    // Safety check, if below 0, then immediatly return the ambient light (should not be here)
    if (params.level < 0) return result;

    // Finding the intersection
    IntersectionParameters intersect_params;
    intersect_params.self_object_index = params.self_object_index;
    auto closest_intersection_result   = closestIntersection(ray, intersect_params);
    if (!closest_intersection_result.has_value()) return result;  // Return sky colour!!!!

    const Intersection &intersection = closest_intersection_result.value().intersection;
    const size_t &object_index       = closest_intersection_result.value().object_index;
    const Object &object             = objects[object_index];
    const Material &material         = object.material;

    // Computing the colour
    glm::vec3 phong_colour         = {0.f, 0.f, 0.f};
    const PhongProperties &phong_p = material.phong_properties;

    // Add ambient lighting always
    phong_colour += phong_p.Ia(ambient_light.colour);

    // Detemine if this object is in shadow
    glm::vec3 l_v   = point_light.position - intersection.position;
    float l_dis     = glm::length(l_v);
    glm::vec3 l_dir = glm::normalize(l_v);
    glm::vec3 v_dir = glm::normalize(ray.origin - intersection.position);

    phong_colour += phong_p.Id(point_light.colour, l_dir, intersection.normal);
    phong_colour += phong_p.Is(point_light.colour, l_dir, v_dir, intersection.normal);

    result.colour = phong_colour;
    return result;
}

std::optional<IntersectionResult> Scene::closestIntersection(const Ray &ray, IntersectionParameters params)
{
    // Find the closest intersection
    double min_valid_distance = std::numeric_limits<float>::max();
    Intersection best_inter;
    std::optional<size_t> best_object_index = std::nullopt;

    for (size_t object_index = 0u; object_index < objects.size(); object_index++) {
        const Object &object = objects[object_index];

        if (!object.shape) continue;

        // What if the ray starts on the surface of an object? What could happen?

        std::optional<Intersection> op_inter = object.shape->getFirstIntersection(ray);
        if (op_inter.has_value()) {
            const Intersection &inter = op_inter.value();

            if (min_valid_distance <= inter.distance) continue;

            min_valid_distance = inter.distance;
            best_inter         = inter;
            best_object_index  = object_index;
        }
    }

    if (!best_object_index.has_value()) return std::nullopt;
    return IntersectionResult{best_inter, best_object_index.value()};
}
