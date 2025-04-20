#include <algorithm>

#include "Scene.h"

#include "../Log.h"

TraceResult Scene::trace(const Ray &ray, TraceParameters params)
{
    TraceResult result;
    result.colour = sky_colour;

    // Safety check, if below 0, then immediatly return the ambient light (should not be here)
    // if (params.level < 0) return result;

    // Finding the intersection
    IntersectionParameters intersect_params;
    intersect_params.self_object_index = params.self_object_index;
    auto closest_intersection_result   = closestIntersection(ray, intersect_params);
    if (!closest_intersection_result.has_value()) return result;  // Return sky colour!!!!

    const Intersection &intersection = closest_intersection_result->intersection;
    const size_t object_index        = closest_intersection_result->object_index;
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

    // PART 4 - Cast a shadow ray to see if light is occluded
    // the ray begins a little below the surface and points towards the light source
    Ray shadow_raycast(intersection.position - intersection.normal * intersect_params.self_eps, l_dir);
    
    // intersection paramters for a shadow ray
    IntersectionParameters shadow_parameters;
    shadow_parameters.self_object_index = object_index;

    // to check if an object lies between the shadow ray and the light source
    // find the closest intersection, and check if it occurs before the light
    // i.e. < l_dis
    auto closest_intersection = closestIntersection(shadow_raycast, shadow_parameters);
    bool is_occluded = closest_intersection && closest_intersection->intersection.distance < l_dis;

    // Only need to add diffuse and specular if not in shadow
    // otherwise same calculation.
    if (!is_occluded) {
        phong_colour += phong_p.Id(point_light.colour, l_dir, intersection.normal);
        phong_colour += phong_p.Is(point_light.colour, l_dir, v_dir, intersection.normal);
    }

    // PART 5 - If object has mirror properties, add reflections.
    // I put the params.level safety check here
    if (material.hasMirrorProperties() && params.level > 0) {

        // Reflection direction is computed by flipping the view direction -v_dir
        // about the surface normal.
        glm::vec3 reflect_direction = glm::reflect(-v_dir, glm::normalize(intersection.normal));

        // Create a new Ray object for the reflected ray that is offset from the intersection.
        Ray reflected_ray = Ray(intersection.position + reflect_direction * intersect_params.self_eps, reflect_direction);

        // parameters for reflected ray
        TraceParameters reflect_parameters;
        reflect_parameters.level = params.level - 1; // ensures recursion terminates at some point
        reflect_parameters.self_object_index = object_index;

        // Recursive call: store the colour of the new reflected ray, calculated by Scene::trace
        // in a Traceresult object. That's the colour that will ultimately be mixed with the 
        // present phong_colour.
        TraceResult reflect_result = trace(reflected_ray, reflect_parameters);

        // Blending the reflected colour and phong colour using the mirror weight
        // glm::mix LERPS between the current phong colour and the 
        // result of the reflection according to the mirror.weight property.
        const MirrorProperties &mirror = *material.mirror_properties;
        phong_colour = glm::mix(phong_colour, reflect_result.colour, mirror.weight);
    }

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
            
            // two checks needed, first prevents self shadowing by skipping object of ray origin
            // the second skips an intersection if it occurs closer to the origin than the 
            // epsilon term 0.001f.
            if (object_index == params.self_object_index) continue;
            if (inter.distance < params.self_eps) continue;
            if (min_valid_distance <= inter.distance) continue;

            min_valid_distance = inter.distance;
            best_inter         = inter;
            best_object_index  = object_index;
        }
    }

    if (!best_object_index.has_value()) return std::nullopt;
    return IntersectionResult{best_inter, best_object_index.value()};
}
