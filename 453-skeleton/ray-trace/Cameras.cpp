#include "Cameras.h"

float Camera::aspectRatio() const { return static_cast<float>(dimensions.x) / static_cast<float>(dimensions.y); }

glm::vec3 Camera::upDirection() const
{
    glm::vec3 up_parallel = glm::dot(approx_up, direction) / glm::dot(direction, direction) * direction;
    return glm::normalize(approx_up - up_parallel);
}

glm::vec3 Camera::rightDirection() const { return glm::normalize(glm::cross(direction, approx_up)); }

std::vector<CameraRay> Camera::generateRays() const
{
    std::vector<CameraRay> ret(dimensions.x * dimensions.y);
    for (size_t x_i = 0u; x_i < dimensions.x; x_i++)
        for (size_t y_i = 0u; y_i < dimensions.y; y_i++)
            ret[x_i + dimensions.x * y_i].pixel = {x_i, y_i};
    return ret;
}

std::vector<CameraRay> OrthographicCamera::generateRays() const
{
    glm::vec3 right = rightDirection();
    glm::vec3 up    = upDirection();

    float ds        = vertical_scale / static_cast<float>(dimensions.y);
    glm::vec3 dx    = ds * right;
    glm::vec3 dy    = ds * up;

    glm::vec3 p_root = position;
    p_root -= 0.5f * vertical_scale * aspectRatio() * right; //move to left edge
    p_root += 0.5f * dx; //Move right half a pixel
    p_root -= 0.5f * vertical_scale * up; //move to bottom edge
    p_root += 0.5f * dy; //Move up half a pixel

    std::vector<CameraRay> ret = Camera::generateRays();
    for (CameraRay& camera_ray : ret) {
        float x_i_f = static_cast<float>(camera_ray.pixel.x);
        float y_i_f = static_cast<float>(camera_ray.pixel.y);
        camera_ray.ray.origin = p_root + (x_i_f * dx) + (y_i_f * dy);
        camera_ray.ray.direction = direction;
    }
    return ret;
}

std::vector<CameraRay> PerspectiveCamera::generateRays() const { 
    

    glm::vec3 forward = glm::normalize(direction); // camera z axis.
    glm::vec3 right = rightDirection();
    glm::vec3 up = upDirection();

    // Step 1: Compute image plane dimensions at z = -1
    float image_plane_height = 2.f * std::tan(vertical_fov_radians / 2.f);
    float image_plane_width = image_plane_height * aspectRatio();

    glm::vec3 image_center = position + forward;
    glm::vec3 horizontal = image_plane_width * right;
    glm::vec3 vertical = image_plane_height * up;

    glm::vec3 bottom_left = image_center - 0.5f * horizontal - 0.5f * vertical;

    std::vector<CameraRay> ret = Camera::generateRays();
    for (CameraRay& camera_ray : ret) {
        float x_i_f = static_cast<float>(camera_ray.pixel.x);
        float y_i_f = static_cast<float>(camera_ray.pixel.y);

        // convert the pixel coords to u,v coords in [0,1]
        float u = (x_i_f + 0.5f) / static_cast<float>(dimensions.x);
        float v = (y_i_f + 0.5f) / static_cast<float>(dimensions.y);

        glm::vec3 pixel_position = bottom_left + u * horizontal + v * vertical;
        glm::vec3 ray_direction = glm::normalize(pixel_position - position);
        camera_ray.ray = Ray(position, ray_direction);
    }

    return ret;
}
