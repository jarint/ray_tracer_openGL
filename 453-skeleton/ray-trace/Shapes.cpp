#include <limits>

#include "Shapes.h"

float Shape::default_eps = 1e-8f;

std::optional<Intersection> Shape::getFirstIntersection(Ray ray, float eps) const { return std::nullopt; }

std::optional<Intersection> Plane::getFirstIntersection(Ray ray, float eps) const { return std::nullopt; }

std::optional<Intersection> AxisAlignedBox::getFirstIntersection(Ray ray, float eps) const
{
    ray = ray.normalize();

    glm::vec3 inv_dir = 1.f / ray.direction;
    glm::vec3 t0s     = (min_bounds - ray.origin) * inv_dir;
    glm::vec3 t1s     = (max_bounds - ray.origin) * inv_dir;

    glm::vec3 tmins = glm::min(t0s, t1s);
    glm::vec3 tmaxs = glm::max(t0s, t1s);

    float t_near = glm::max(tmins.x, glm::max(tmins.y, tmins.z));
    float t_far  = glm::min(tmaxs.x, glm::min(tmaxs.y, tmaxs.z));

    // If the ray misses the box
    if (t_near > t_far || t_far < eps) return std::nullopt;

    // Select the smallest positive t value
    float t = (t_near > eps) ? t_near : t_far;

    // Compute the intersection point
    Intersection ret;
    ret.position = ray.origin + ray.direction * t;
    ret.distance = t;

    bool inside = t_near < eps;

    ret.normal = {0.f, 0.f, 0.f};
    if (!inside) {
        if (t_near == tmins.x) ret.normal = {-glm::sign(ray.direction.x), 0.f, 0.f};
        else if (t_near == tmins.y) ret.normal = {0.f, -glm::sign(ray.direction.y), 0.f};
        else if (t_near == tmins.z) ret.normal = {0.f, 0.f, -glm::sign(ray.direction.z)};
    }
    else {
        if (t_far == tmaxs.x) ret.normal = {glm::sign(ray.direction.x), 0.f, 0.f};
        else if (t_far == tmaxs.y) ret.normal = {0.f, glm::sign(ray.direction.y), 0.f};
        else if (t_far == tmaxs.z) ret.normal = {0.f, 0.f, glm::sign(ray.direction.z)};
    }

    return ret;
}

std::optional<Intersection> Triangle::getFirstIntersection(Ray ray, float eps) const
{
    // From https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm

    ray = ray.normalize();

    glm::vec3 e1 = p1 - p0;
    glm::vec3 e2 = p2 - p0;

    glm::vec3 h = glm::cross(ray.direction, e2);
    float a     = glm::dot(e1, h);

    // If determinant is close to zero, the ray is nearly parallel to the triangle
    if (glm::abs(a) < eps) return std::nullopt;

    float f     = 1.f / a;
    glm::vec3 s = ray.origin - p0;
    float u     = f * glm::dot(s, h);

    // Compute u parameter and test bounds, u should be in [0,1]
    if (u < 0.f || u > 1.f) return std::nullopt;

    glm::vec3 q = glm::cross(s, e1);
    float v     = f * glm::dot(ray.direction, q);

    // Compute v parameter and test bounds, v should be in [0,1] and u + v ≤ 1
    if (v < 0.f || u + v > 1.f) return std::nullopt;

    float t = f * glm::dot(e2, q);

    // Ignore intersections behind the ray origin or directly ontop
    if (t <= eps) return std::nullopt;

    Intersection ret;
    ret.position = ray.origin + ray.direction * t;
    ret.normal   = glm::normalize(glm::cross(e1, e2));
    ret.distance = t;
    return ret;
}

std::optional<Intersection> TriangleSoup::getFirstIntersection(Ray ray, float eps) const
{
    double min_valid_distance       = std::numeric_limits<float>::max();
    std::optional<Intersection> ret = std::nullopt;
    for (const Triangle &triangle : triangles) {
        std::optional<Intersection> op_inter = triangle.getFirstIntersection(ray);
        if (op_inter.has_value()) {
            const Intersection &inter = op_inter.value();
            if (min_valid_distance > inter.distance) {
                ret                = op_inter;
                min_valid_distance = inter.distance;
            }
        }
    }
    return ret;
}

std::optional<Intersection> Sphere::getFirstIntersection(Ray ray, float eps) const { return std::nullopt; }

std::optional<Intersection> InfiniteCylinder::getFirstIntersection(Ray ray, float eps) const { return std::nullopt; }

std::optional<Intersection> Cylinder::getFirstIntersection(Ray ray, float eps) const { return std::nullopt; }
