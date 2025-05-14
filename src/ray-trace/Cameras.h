#pragma once
#include <vector>

#include <glm/glm.hpp>

#include "Ray.h"

struct CameraRay
{
    CameraRay(Ray init_ray = Ray(), glm::uvec2 init_pixel = {0u, 0u})
        : ray(init_ray)
        , pixel(init_pixel)
    {
    }
    Ray ray;
    glm::uvec2 pixel;
};

struct Camera {
    Camera(
        glm::vec3 init_position    = {0.f, 0.f, 0.f},
        glm::vec3 init_direction   = {0.f, 0.f, -1.f},
        glm::vec3 init_approx_up = {0.f, 1.f, 0.f},
        glm::uvec2 init_dimensions = {800u, 800u}
    )
        : position(init_position)
        , direction(init_direction)
        , approx_up(init_approx_up)
        , dimensions(init_dimensions)
    {
    }

    float aspectRatio() const;
    glm::vec3 upDirection() const;
    glm::vec3 rightDirection() const;
    virtual std::vector<CameraRay> generateRays() const;

    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 approx_up;
    glm::uvec2 dimensions;
};

struct OrthographicCamera : public Camera {
    OrthographicCamera(
        glm::vec3 init_position    = {0.f, 0.f, 0.f},
        glm::vec3 init_direction   = {0.f, 0.f, -1.f},
        glm::vec3 init_approx_up   = {0.f, 1.f, 0.f},
        glm::uvec2 init_dimensions = {800u, 800u},
        float init_vertical_scale  = 16.f
    )
        : Camera(init_position, init_direction, init_approx_up, init_dimensions)
        , vertical_scale(init_vertical_scale)
    {
    }

    virtual std::vector<CameraRay> generateRays() const;

    float vertical_scale;
};

struct PerspectiveCamera : public Camera {
    PerspectiveCamera(
        glm::vec3 init_position         = {0.f, 0.f, 0.f},
        glm::vec3 init_direction        = {0.f, 0.f, -1.f},
        glm::vec3 init_approx_up        = {0.f, 1.f, 0.f},
        glm::uvec2 init_dimensions      = {800u, 800u},
        float init_vertical_fov_radians = glm::radians(60.f)
    )
        : Camera(init_position, init_direction, init_approx_up, init_dimensions)
        , vertical_fov_radians(init_vertical_fov_radians)
    {
    }

    // ---- NOT IMPLEMENTED ---- //
    virtual std::vector<CameraRay> generateRays() const;

    float vertical_fov_radians;
};
