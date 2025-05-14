#pragma once
#include <optional>
#include <vector>

#include <glm/glm.hpp>

#include "Intersections.h"
#include "Ray.h"

struct Shape {
    Shape()
        : possible_self_occlusion(false)
    {
    }

    virtual std::optional<Intersection> getFirstIntersection(Ray ray, float eps = Shape::default_eps) const;
    static float default_eps;

    bool possibleSelfOcclusion() const { return possible_self_occlusion; }

  protected:
    bool possible_self_occlusion;
};

struct Plane : public Shape {
    Plane(glm::vec3 init_position = {0.f, 0.f, 0.f}, glm::vec3 init_normal = {0.f, 0.f, 1.f})
        : position(init_position)
        , normal(init_normal)
    {
    }

    // ---- NOT IMPLEMENTED ---- //
    std::optional<Intersection> getFirstIntersection(Ray ray, float eps = Shape::default_eps) const override;

    glm::vec3 position;
    glm::vec3 normal;
};

struct AxisAlignedBox : public Shape {
    AxisAlignedBox(glm::vec3 init_min_bounds = {-0.5f, -0.5f, -0.5f}, glm::vec3 init_max_bounds = {0.5f, 0.5f, 0.5f})
        : min_bounds(init_min_bounds)
        , max_bounds(init_max_bounds)
    {
    }

    std::optional<Intersection> getFirstIntersection(Ray ray, float eps = Shape::default_eps) const override;

    glm::vec3 min_bounds;
    glm::vec3 max_bounds;
};

struct Triangle : public Shape {
    Triangle(glm::vec3 init_p0 = {0.f, 0.f, 0.f}, glm::vec3 init_p1 = {0.f, 0.f, 0.f}, glm::vec3 init_p2 = {0.f, 0.f, 0.f})
        : p0(init_p0)
        , p1(init_p1)
        , p2(init_p2)
    {
    }

    std::optional<Intersection> getFirstIntersection(Ray ray, float eps = Shape::default_eps) const override;

    glm::vec3 p0;
    glm::vec3 p1;
    glm::vec3 p2;
};

struct TriangleSoup : public Shape {
    TriangleSoup(std::vector<Triangle> init_triangles = {})
        : triangles(init_triangles)
    {
        possible_self_occlusion = true;
    }

    std::optional<Intersection> getFirstIntersection(Ray ray, float eps = Shape::default_eps) const override;

    std::vector<Triangle> triangles;
};

struct Sphere : public Shape {
    Sphere(glm::vec3 init_position = {0.f, 0.f, 0.f}, float init_radius = 1.f)
        : position(init_position)
        , radius(init_radius)
    {
    }

    // ---- NOT IMPLEMENTED ---- //
    std::optional<Intersection> getFirstIntersection(Ray ray, float eps = Shape::default_eps) const override;

    glm::vec3 position;
    float radius;
};

struct InfiniteCylinder : public Shape {
    InfiniteCylinder(
        glm::vec3 init_position       = {0.f, 0.f, 0.f},
        glm::vec3 init_axis_direction = {1.f, 0.f, 0.f},
        float init_radius             = 1.f
    )
        : position(init_position)
        , axis_direction(init_axis_direction)
        , radius(init_radius)
    {
    }

    // ---- NOT IMPLEMENTED ---- //
    std::optional<Intersection> getFirstIntersection(Ray ray, float eps = Shape::default_eps) const override;

    glm::vec3 position;
    glm::vec3 axis_direction;
    float radius;
};

struct Cylinder : public InfiniteCylinder {
    Cylinder(
        glm::vec3 init_position       = {0.f, 0.f, 0.f},
        glm::vec3 init_axis_direction = {1.f, 0.f, 0.f},
        float init_radius             = 1.f,
        float init_length             = 1.f // Length along the axis direction starting on position
    )
        : InfiniteCylinder(init_position, init_axis_direction, init_radius)
        , length(init_length)
    {
    }

    // ---- NOT IMPLEMENTED ---- //
    std::optional<Intersection> getFirstIntersection(Ray ray, float eps = Shape::default_eps) const override;

    float length;
};
