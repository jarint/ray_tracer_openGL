#include "RayTracingBaselineScenes.h"

#include <glm/gtx/transform.hpp>



TriangleSoup ringGeometry(const glm::mat4 &transform)
{
    std::vector<glm::vec3> vertices
        = {{-1.000000, -0.250000, 1.000000},
           {1.000000, -0.250000, 1.000000},
           {-1.000000, -0.250000, -1.000000},
           {1.000000, -0.250000, -1.000000},
           {-0.700000, -0.250000, 0.700000},
           {-0.700000, -0.250000, -0.700000},
           {0.700000, -0.250000, 0.700000},
           {0.700000, -0.250000, -0.700000},
           {-1.000000, 0.250000, -1.000000},
           {-1.000000, 0.250000, 1.000000},
           {1.000000, 0.250000, 1.000000},
           {1.000000, 0.250000, -1.000000},
           {-0.700000, 0.250000, 0.700000},
           {-0.700000, 0.250000, -0.700000},
           {0.700000, 0.250000, 0.700000},
           {0.700000, 0.250000, -0.700000}};
    std::vector<std::vector<int>> faces
        = {{1, 4, 6},   {0, 5, 4},   {5, 3, 7},   {6, 3, 1}, {12, 10, 14}, {13, 9, 12}, {11, 13, 15}, {11, 14, 10},
           {4, 14, 6},  {5, 12, 4},  {3, 10, 1},  {0, 8, 2}, {7, 13, 5},   {6, 15, 7},  {2, 11, 3},   {1, 9, 0},
           {1, 0, 4},   {0, 2, 5},   {5, 2, 3},   {6, 7, 3}, {12, 9, 10},  {13, 8, 9},  {11, 8, 13},  {11, 15, 14},
           {4, 12, 14}, {5, 13, 12}, {3, 11, 10}, {0, 9, 8}, {7, 15, 13},  {6, 14, 15}, {2, 8, 11},   {1, 10, 9}};

    std::vector<glm::vec3> transformedVertices;
    for (const auto &vertex : vertices) {
        glm::vec4 transformedVertex = transform * glm::vec4(vertex, 1.0f);
        transformedVertices.push_back(glm::vec3(transformedVertex));
    }

    std::vector<Triangle> triangles;
    for (const auto &f : faces)
        triangles.emplace_back(transformedVertices[f[0]], transformedVertices[f[1]], transformedVertices[f[2]]);
    return TriangleSoup(triangles);
}

TriangleSoup triangularPyramidGeometry(const glm::mat4 &transform)
{
    std::vector<glm::vec3> vertices
        = {{0.000000, 0.000000, -1.000000},
           {0.866025, 0.000000, 0.500000},
           {-0.866025, 0.000000, 0.500000},
           {0.000000, 1.000000, 0.000000}};
    std::vector<std::vector<int>> faces = {{0, 3, 1}, {0, 1, 2}, {1, 3, 2}, {2, 3, 0}};

    std::vector<glm::vec3> transformedVertices;
    for (const auto &vertex : vertices) {
        glm::vec4 transformedVertex = transform * glm::vec4(vertex, 1.0f);
        transformedVertices.push_back(glm::vec3(transformedVertex));
    }
    std::vector<Triangle> triangles;
    for (const auto &f : faces)
        triangles.emplace_back(transformedVertices[f[0]], transformedVertices[f[1]], transformedVertices[f[2]]);
    return TriangleSoup(triangles);
}

Scene RayTracingBaselineScenes::A()
{
    Scene scene;

    scene.sky_colour           = {0.529f, 0.808f, 0.922f};
    scene.ambient_light.colour = {0.2f, 0.2f, 0.2f};
    scene.point_light.colour   = {1.0f, 1.0f, 1.0f};
    scene.point_light.position = {5.0f, 10.0f, 5.0f};

    // Floor
    Material floor_m;
    floor_m.phong_properties.weight            = 1.0f;
    floor_m.phong_properties.colour            = {0.4f, 0.7f, 0.3f};
    floor_m.phong_properties.ambient_strength  = 0.1f;
    floor_m.phong_properties.diffuse_strength  = 0.9f;
    floor_m.phong_properties.specular_strength = 0.9f;
    floor_m.phong_properties.shininess         = 512.f;

    auto floor_g      = std::make_shared<Plane>();
    floor_g->position = {0.f, 0.f, 0.f};
    floor_g->normal   = {0.f, 1.f, 0.f};
    scene.objects.push_back(Object(floor_g, floor_m));

    // Boxes
    Material box_m;
    box_m.phong_properties.weight            = 1.0f;
    box_m.phong_properties.colour            = {0.76f, 0.60f, 0.42f};
    box_m.phong_properties.ambient_strength  = 0.1f;
    box_m.phong_properties.diffuse_strength  = 0.8f;
    box_m.phong_properties.specular_strength = 0.8f;
    box_m.phong_properties.shininess         = 64.f;

    for (float x = -5.f; x <= 5.f; x += 5.f) {
        for (float z = -5.f; z <= 5.f; z += 5.f) {
            auto box_g        = std::make_shared<AxisAlignedBox>();  // New one as the old one will still point to the same object
            box_g->min_bounds = {x - 2.f, 0.0001f, z - 2.f};
            float height      = (glm::abs(x) + glm::abs(z)) < 2.5f ? 4.0f : 1.0f;
            box_g->max_bounds = {x + 2.f, height, z + 2.f};
            scene.objects.push_back(Object(box_g, box_m));
        }
    }

    return scene;
}

Scene RayTracingBaselineScenes::B()
{
    Scene scene;

    scene.sky_colour           = {0.529f, 0.808f, 0.922f};
    scene.ambient_light.colour = {0.2f, 0.2f, 0.2f};
    scene.point_light.colour   = {1.0f, 1.0f, 1.0f};
    scene.point_light.position = {5.0f, 10.0f, 5.0f};

    // Floor
    Material floor_m;
    floor_m.phong_properties.weight            = 1.0f;
    floor_m.phong_properties.colour            = {0.4f, 0.7f, 0.3f};
    floor_m.phong_properties.ambient_strength  = 0.1f;
    floor_m.phong_properties.diffuse_strength  = 0.9f;
    floor_m.phong_properties.specular_strength = 0.9f;
    floor_m.phong_properties.shininess         = 512.f;

    auto floor_g      = std::make_shared<Plane>();
    floor_g->position = {0.f, 0.f, 0.f};
    floor_g->normal   = {0.f, 1.f, 0.f};
    scene.objects.push_back(Object(floor_g, floor_m));

    // Spheres
    Material sphere_m;
    sphere_m.phong_properties.weight            = 1.0f;
    sphere_m.phong_properties.colour            = {0.8f, 0.1f, 0.2f};
    sphere_m.phong_properties.ambient_strength  = 0.1f;
    sphere_m.phong_properties.diffuse_strength  = 0.8f;
    sphere_m.phong_properties.specular_strength = 0.8f;
    sphere_m.phong_properties.shininess         = 256.f;

    for (float x = -5.f; x <= 5.f; x += 5.f) {
        for (float z = -5.f; z <= 5.f; z += 5.f) {
            auto sphere_g      = std::make_shared<Sphere>();  // New one as the old one will still point to the same object
            bool is_middle     = (glm::abs(x) + glm::abs(z)) < 2.5f;
            sphere_g->radius   = is_middle ? 3.f : 1.5f;
            sphere_g->position = {x, sphere_g->radius + 0.0001f, z};
            scene.objects.push_back(Object(sphere_g, sphere_m));
        }
    }

    return scene;
}

Scene RayTracingBaselineScenes::C()
{
    Scene scene;

    scene.sky_colour           = {0.529f, 0.808f, 0.922f};
    scene.ambient_light.colour = {0.2f, 0.2f, 0.2f};
    scene.point_light.colour   = {1.0f, 1.0f, 1.0f};
    scene.point_light.position = {5.0f, 10.0f, 5.0f};

    // Floor
    Material floor_m;
    floor_m.phong_properties.weight            = 1.0f;
    floor_m.phong_properties.colour            = {0.4f, 0.7f, 0.3f};
    floor_m.phong_properties.ambient_strength  = 0.1f;
    floor_m.phong_properties.diffuse_strength  = 0.9f;
    floor_m.phong_properties.specular_strength = 0.9f;
    floor_m.phong_properties.shininess         = 512.f;

    auto floor_g      = std::make_shared<Plane>();
    floor_g->position = {0.f, 0.f, 0.f};
    floor_g->normal   = {0.f, 1.f, 0.f};
    scene.objects.push_back(Object(floor_g, floor_m));

    // Ring
    Material ring_m;
    ring_m.phong_properties.weight            = 1.0f;
    ring_m.phong_properties.colour            = {0.8f, 0.0f, 0.0f};
    ring_m.phong_properties.ambient_strength  = 0.1f;
    ring_m.phong_properties.diffuse_strength  = 0.9f;
    ring_m.phong_properties.specular_strength = 0.0f;
    ring_m.phong_properties.shininess         = 512.f;

    glm::mat4 ring_t_s = glm::scale(glm::mat4(1.f), glm::vec3(3.f));
    glm::mat4 ring_t_r = glm::rotate(glm::mat4(1.f), glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
    glm::mat4 ring_t_t = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 3.f, 0.f));
    auto ring_g        = std::make_shared<TriangleSoup>(ringGeometry(ring_t_t * ring_t_r * ring_t_s));
    scene.objects.push_back(Object(ring_g, ring_m));

    return scene;
}

Scene RayTracingBaselineScenes::D()
{
    Scene scene;

    scene.sky_colour           = {0.529f, 0.808f, 0.922f};
    scene.ambient_light.colour = {0.2f, 0.2f, 0.2f};
    scene.point_light.colour   = {1.0f, 1.0f, 1.0f};
    scene.point_light.position = {5.0f, 10.0f, 5.0f};

    // Floor
    Material floor_m;
    floor_m.phong_properties.weight            = 0.7f;
    floor_m.phong_properties.colour            = {0.4f, 0.7f, 0.3f};
    floor_m.phong_properties.ambient_strength  = 0.1f;
    floor_m.phong_properties.diffuse_strength  = 0.9f;
    floor_m.phong_properties.specular_strength = 0.9f;
    floor_m.phong_properties.shininess         = 512.f;

    auto floor_g      = std::make_shared<Plane>();
    floor_g->position = {0.f, 0.f, 0.f};
    floor_g->normal   = {0.f, 1.f, 0.f};
    scene.objects.push_back(Object(floor_g, floor_m));

    // Spheres
    Material sphere_m;
    sphere_m.phong_properties.weight            = 0.2f;
    sphere_m.phong_properties.colour            = {0.3f, 0.4f, 0.4f};
    sphere_m.phong_properties.ambient_strength  = 0.1f;
    sphere_m.phong_properties.diffuse_strength  = 0.8f;
    sphere_m.phong_properties.specular_strength = 0.8f;
    sphere_m.phong_properties.shininess         = 1024.f;
    sphere_m.mirror_properties                  = MirrorProperties(1.f - sphere_m.phong_properties.weight);

    auto sphere_1_g      = std::make_shared<Sphere>();
    sphere_1_g->radius   = 4.5f;
    sphere_1_g->position = {5.f, sphere_1_g->radius + 5.f, -5.f};
    scene.objects.push_back(Object(sphere_1_g, sphere_m));

    auto sphere_2_g      = std::make_shared<Sphere>();
    sphere_2_g->radius   = 4.5f;
    sphere_2_g->position = {-5.f, sphere_1_g->radius + 5.f, -5.f};
    scene.objects.push_back(Object(sphere_2_g, sphere_m));

    // Boxes
    Material box_m;
    box_m.phong_properties.weight            = 0.8f;
    box_m.phong_properties.colour            = {0.76f, 0.60f, 0.42f};
    box_m.phong_properties.ambient_strength  = 0.1f;
    box_m.phong_properties.diffuse_strength  = 0.8f;
    box_m.phong_properties.specular_strength = 0.8f;
    box_m.phong_properties.shininess         = 256.f;
    box_m.mirror_properties                  = MirrorProperties(1.f - box_m.phong_properties.weight);

    for (float x = -5.f; x <= 5.f; x += 5.f) {
        for (float z = -5.f; z <= 5.f; z += 5.f) {
            auto box_g        = std::make_shared<AxisAlignedBox>();  // New one as the old one will still point to the same object
            box_g->min_bounds = {x - 2.f, 0.0001f, z - 2.f};
            float height      = (glm::abs(x) + glm::abs(z)) < 2.5f ? 5.0f : 1.0f;
            box_g->max_bounds = {x + 2.f, height, z + 2.f};
            scene.objects.push_back(Object(box_g, box_m));
        }
    }

    return scene;
}

Scene RayTracingBaselineScenes::E()
{
    Scene scene;

    scene.sky_colour           = {0.529f, 0.808f, 0.922f};
    scene.ambient_light.colour = {0.2f, 0.2f, 0.2f};
    scene.point_light.colour   = {1.0f, 1.0f, 1.0f};
    scene.point_light.position = {20.0f, 20.0f, 20.0f};

    // Floor
    Material floor_m;
    floor_m.phong_properties.weight            = 1.0f;
    floor_m.phong_properties.colour            = {0.4f, 0.7f, 0.3f};
    floor_m.phong_properties.ambient_strength  = 0.1f;
    floor_m.phong_properties.diffuse_strength  = 0.9f;
    floor_m.phong_properties.specular_strength = 0.9f;
    floor_m.phong_properties.shininess         = 512.f;

    auto floor_g      = std::make_shared<Plane>();
    floor_g->position = {0.f, 0.f, 0.f};
    floor_g->normal   = {0.f, 1.f, 0.f};
    scene.objects.push_back(Object(floor_g, floor_m));

    // Inf Cylinder
    Material inf_cylinder_m;
    inf_cylinder_m.phong_properties.weight            = 0.7f;
    inf_cylinder_m.phong_properties.colour            = {0.2f, 0.87f, 0.42f};
    inf_cylinder_m.phong_properties.ambient_strength  = 0.1f;
    inf_cylinder_m.phong_properties.diffuse_strength  = 0.8f;
    inf_cylinder_m.phong_properties.specular_strength = 0.8f;
    inf_cylinder_m.phong_properties.shininess         = 128.f;
    inf_cylinder_m.mirror_properties                  = MirrorProperties(1.f - inf_cylinder_m.phong_properties.weight);

    auto inf_cylinder_g            = std::make_shared<InfiniteCylinder>();
    inf_cylinder_g->position       = {0.f, 4.f, -5.f};
    inf_cylinder_g->axis_direction = glm::normalize(glm::vec3{1.f, 0.5f, 0.32f});
    inf_cylinder_g->radius         = 1.454f;
    scene.objects.push_back(Object(inf_cylinder_g, inf_cylinder_m));

    // Cylinder
    Material cylinder_1_m;
    cylinder_1_m.phong_properties.weight                    = 0.1f;
    cylinder_1_m.phong_properties.colour                    = {0.6f, 0.1f, 0.6f};
    cylinder_1_m.phong_properties.ambient_strength          = 0.1f;
    cylinder_1_m.phong_properties.diffuse_strength          = 0.8f;
    cylinder_1_m.phong_properties.specular_strength         = 0.8f;
    cylinder_1_m.phong_properties.shininess                 = 128.f;
    cylinder_1_m.fresnel_properties                         = FresnelProperties();
    cylinder_1_m.fresnel_properties.value().weight          = 1.f - cylinder_1_m.phong_properties.weight;
    cylinder_1_m.fresnel_properties.value().refraction_index = 1.25f;

    auto cylinder_1_g            = std::make_shared<Cylinder>();
    cylinder_1_g->position       = {-3.f, 10.f, 0.f};
    cylinder_1_g->axis_direction = glm::normalize(glm::vec3{-0.3f, -1.f, 0.666f});
    cylinder_1_g->radius         = 2.45f;
    cylinder_1_g->length         = 7.f;
    scene.objects.push_back(Object(cylinder_1_g, cylinder_1_m));

    Material cylinder_2_m;
    cylinder_2_m.phong_properties.weight            = 1.0f;
    cylinder_2_m.phong_properties.colour            = {1.0f, 0.0f, 0.0f};
    cylinder_2_m.phong_properties.ambient_strength  = 0.1f;
    cylinder_2_m.phong_properties.diffuse_strength  = 0.8f;
    cylinder_2_m.phong_properties.specular_strength = 0.8f;
    cylinder_2_m.phong_properties.shininess         = 128.f;

    auto cylinder_2_g            = std::make_shared<Cylinder>();
    cylinder_2_g->position       = {5.f, 0.5f, 5.f};
    cylinder_2_g->axis_direction = glm::normalize(glm::vec3{0.f, 1.f, 0.f});
    cylinder_2_g->radius         = 1.f;
    cylinder_2_g->length         = 2.f;
    scene.objects.push_back(Object(cylinder_2_g, cylinder_2_m));

    return scene;
}

Scene RayTracingBaselineScenes::F()
{
    Scene scene;

    scene.sky_colour           = {0.529f, 0.808f, 0.922f};
    scene.ambient_light.colour = {0.2f, 0.2f, 0.2f};
    scene.point_light.colour   = {1.0f, 1.0f, 1.0f};
    scene.point_light.position = {0.f, 10.f, 5.f};

    float global_ambient_strength = 0.15f;

    // Floor
    Material floor_m;
    floor_m.phong_properties.weight            = 0.95f;
    floor_m.phong_properties.colour            = {0.4f, 0.7f, 0.3f};
    floor_m.phong_properties.ambient_strength  = global_ambient_strength;
    floor_m.phong_properties.diffuse_strength  = 1.f;
    floor_m.phong_properties.specular_strength = 0.1f;
    floor_m.phong_properties.shininess         = 128.f;
    floor_m.mirror_properties                  = MirrorProperties(1.f - floor_m.phong_properties.weight);

    auto floor_g      = std::make_shared<Plane>();
    floor_g->position = {0.f, 0.f, 0.f};
    floor_g->normal   = {0.f, 1.f, 0.f};
    scene.objects.push_back(Object(floor_g, floor_m));

    // Array of Spheres
    Material array_sphere_m;
    array_sphere_m.phong_properties.weight            = 0.7f;
    array_sphere_m.phong_properties.colour            = {0.7f, 0.0f, 0.3f};
    array_sphere_m.phong_properties.ambient_strength  = global_ambient_strength;
    array_sphere_m.phong_properties.diffuse_strength  = 0.8f;
    array_sphere_m.phong_properties.specular_strength = 0.8f;
    array_sphere_m.phong_properties.shininess         = 256.f;
    array_sphere_m.mirror_properties                  = MirrorProperties(1.f - array_sphere_m.phong_properties.weight);

    for (float x = -10.f; x <= 10.f; x += 2.f) {
        for (float z = -10.f; z <= 10.f; z += 2.f) {
            auto array_sphere_g      = std::make_shared<Sphere>();
            array_sphere_g->radius   = glm::sqrt(1.0f - 0.09f * glm::max(glm::abs(x), glm::abs(z)));
            float y                  = array_sphere_g->radius;
            array_sphere_g->position = {x, y, z};
            scene.objects.push_back(Object(array_sphere_g, array_sphere_m));
        }
    }

    // Sphere 1
    Material sphere_1_m;
    sphere_1_m.phong_properties.weight            = 0.01f;
    sphere_1_m.phong_properties.colour            = {0.6f, 0.6f, 0.6f};
    sphere_1_m.phong_properties.ambient_strength  = global_ambient_strength;
    sphere_1_m.phong_properties.diffuse_strength  = 0.4f;
    sphere_1_m.phong_properties.specular_strength = 1.0f;
    sphere_1_m.phong_properties.shininess         = 512.f;
    sphere_1_m.mirror_properties                  = MirrorProperties(1.f - sphere_1_m.phong_properties.weight);

    auto sphere_1_g      = std::make_shared<Sphere>();
    sphere_1_g->position = {-20.f, 15.f, -20.f};
    sphere_1_g->radius   = 8.f;
    scene.objects.push_back(Object(sphere_1_g, sphere_1_m));

    // Ring 1
    Material ring_m_1;
    ring_m_1.phong_properties.weight            = 1.0f;
    ring_m_1.phong_properties.colour            = {0.8f, 0.0f, 0.0f};
    ring_m_1.phong_properties.ambient_strength  = global_ambient_strength;
    ring_m_1.phong_properties.diffuse_strength  = 0.9f;
    ring_m_1.phong_properties.specular_strength = 0.0f;
    ring_m_1.phong_properties.shininess         = 512.f;

    glm::mat4 ring_t_1 = glm::translate(glm::mat4(1.f), glm::vec3(6.5f, 3.f, 14.f))
        * glm::rotate(glm::mat4(1.f), glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f)) * glm::scale(glm::mat4(1.f), glm::vec3(3.f));
    auto ring_g_1 = std::make_shared<TriangleSoup>(ringGeometry(ring_t_1));
    scene.objects.push_back(Object(ring_g_1, ring_m_1));

    // Ring 2
    Material ring_m_2;
    ring_m_1.phong_properties.weight            = 0.85f;
    ring_m_2.phong_properties.colour            = {0.8f, 0.0f, 0.0f};
    ring_m_2.phong_properties.ambient_strength  = global_ambient_strength;
    ring_m_2.phong_properties.diffuse_strength  = 0.8f;
    ring_m_2.phong_properties.specular_strength = 0.8f;
    ring_m_2.phong_properties.shininess         = 64.f;
    ring_m_2.mirror_properties                  = MirrorProperties(1.f - ring_m_1.phong_properties.weight);

    glm::mat4 ring_t_2 = glm::translate(glm::mat4(1.f), glm::vec3(-6.5f, 3.f, 14.f))
        * glm::rotate(glm::mat4(1.f), glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f)) * glm::scale(glm::mat4(1.f), glm::vec3(3.f));
    auto ring_g_2 = std::make_shared<TriangleSoup>(ringGeometry(ring_t_2));
    scene.objects.push_back(Object(ring_g_2, ring_m_2));

    // Triangular Pyramid 1
    Material triangular_pyramid_1_m;
    triangular_pyramid_1_m.phong_properties.weight            = 1.f;
    triangular_pyramid_1_m.phong_properties.colour            = {0.02f, 0.9f, 0.9f};
    triangular_pyramid_1_m.phong_properties.ambient_strength  = global_ambient_strength;
    triangular_pyramid_1_m.phong_properties.diffuse_strength  = 0.9f;
    triangular_pyramid_1_m.phong_properties.specular_strength = 0.3f;
    triangular_pyramid_1_m.phong_properties.shininess         = 256.f;

    glm::mat4 triangular_pyramid_1_t = glm::translate(glm::mat4(1.f), glm::vec3(3.f, 0.0001f, -17.f))
        * glm::rotate(glm::mat4(1.f), glm::radians(90.f), glm::vec3(0.f, 1.f, 0.f)) * glm::scale(glm::mat4(1.f), glm::vec3(8.f));
    auto triangular_pyramid_1_g = std::make_shared<TriangleSoup>(triangularPyramidGeometry(triangular_pyramid_1_t));
    scene.objects.push_back(Object(triangular_pyramid_1_g, triangular_pyramid_1_m));

    // Triangular Pyramid 2
    Material triangular_pyramid_2_m;
    triangular_pyramid_2_m.phong_properties.weight            = 0.05f;
    triangular_pyramid_2_m.phong_properties.colour            = {1.f, 1.f, 1.f};
    triangular_pyramid_2_m.phong_properties.ambient_strength  = global_ambient_strength;
    triangular_pyramid_2_m.phong_properties.diffuse_strength  = 0.0f;
    triangular_pyramid_2_m.phong_properties.specular_strength = 1.0f;
    triangular_pyramid_2_m.phong_properties.shininess         = 1024.f;
    triangular_pyramid_2_m.fresnel_properties = FresnelProperties(1.f - triangular_pyramid_2_m.phong_properties.weight, 1.25f);

    glm::mat4 triangular_pyramid_2_t
        = glm::translate(glm::mat4(1.f), glm::vec3(-16.f, 0.0001f, 0.f)) * glm::scale(glm::mat4(1.f), glm::vec3(5.f));
    auto triangular_pyramid_2_g = std::make_shared<TriangleSoup>(triangularPyramidGeometry(triangular_pyramid_2_t));
    scene.objects.push_back(Object(triangular_pyramid_2_g, triangular_pyramid_2_m));

    // Box 1
    Material box_m;
    box_m.phong_properties.weight            = 0.05f;
    box_m.phong_properties.colour            = {0.6f, 0.6f, 0.6f};
    box_m.phong_properties.ambient_strength  = global_ambient_strength;
    box_m.phong_properties.diffuse_strength  = 0.4f;
    box_m.phong_properties.specular_strength = 1.0f;
    box_m.phong_properties.shininess         = 512.f;
    box_m.fresnel_properties                 = FresnelProperties(1.f - box_m.phong_properties.weight, 1.5f);

    auto box_g        = std::make_shared<AxisAlignedBox>();
    box_g->min_bounds = {14.f, 0.0001f, -20.f};
    box_g->max_bounds = {16.f, 10.f, 20.f};
    scene.objects.push_back(Object(box_g, box_m));

    return scene;
}
