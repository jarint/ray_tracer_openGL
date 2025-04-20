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
    /*
     * generates a ray for each pixel following perspective projection
     * uses vertical FOV and aspect ratio to compute the image plane size
     * the plane begins 1 unit in front of the camera and each pixel
     * is mapped to a point on the plane. A ray is cast from the 
     * camera through that point.   
     */

    glm::vec3 forward = glm::normalize(direction); // camera z axis.
    glm::vec3 right = rightDirection();
    glm::vec3 up = upDirection();

    // size of the image plane 1 unit from the camera
    // width is scaled using the aspect ration, vertical FOV spans from top to bottom of the image plane
    float height = 2.f * std::tan(vertical_fov_radians / 2.f);
    float width = height * aspectRatio();
    // world space center of hte image plane.
    glm::vec3 center = position + forward;
    // horizontal and vertical vectors scaled to image plane size
    glm::vec3 horizontal = width * right;
    glm::vec3 vertical = height * up;
    // camera-relative origin calculation
    glm::vec3 left_offset = -0.5f * horizontal;  // offset left by half the image width
    glm::vec3 down_offset = -0.5f * vertical;    // offset down by half the image height
    glm::vec3 origin = center + left_offset + down_offset;

    // ray to pixel mapping
    std::vector<CameraRay> ret = Camera::generateRays();
    for (CameraRay& camera_ray : ret) {
        float x_i_f = static_cast<float>(camera_ray.pixel.x);
        float y_i_f = static_cast<float>(camera_ray.pixel.y);

        // convert the pixel coords to u,v coords in [0,1]
        float u = (x_i_f + 0.5f) / static_cast<float>(dimensions.x);
        float v = (y_i_f + 0.5f) / static_cast<float>(dimensions.y);

        // position of the pixel in world-space
        glm::vec3 pixel_position = origin + u * horizontal + v * vertical;

        // direction from camera to pixel, normalized
        glm::vec3 ray_direction = glm::normalize(pixel_position - position);

        // create the ray
        camera_ray.ray = Ray(position, ray_direction);
    }

    return ret;
}
