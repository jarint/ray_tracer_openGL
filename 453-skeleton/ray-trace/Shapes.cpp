#include <limits>

#include "Shapes.h"

float Shape::default_eps = 1e-8f;

std::optional<Intersection> Shape::getFirstIntersection(Ray ray, float eps) const { return std::nullopt; }

std::optional<Intersection> Plane::getFirstIntersection(Ray ray, float eps) const { 
    ray = ray.normalize();

    // the bottom term for the intersection formula is the dot product 
    // of the ray direction and plane normal. when very close to 0,
    // the ray is roughly parallel and should not intersect
    float intersect_term = glm::dot(ray.direction, normal);
    // Ray is parallel to the plane
    if (glm::abs(intersect_term) < eps) return std::nullopt;

    // distance t from ray origin to the intersection.
    // if negative or very small, may cause self intersection.
    float sol = glm::dot(position - ray.origin, normal) / intersect_term;
    if (sol < eps) return std::nullopt;

    // valid intersection gets returned
    Intersection result;
    result.position = ray.origin + sol * ray.direction; // intersection
    result.normal   = normal;
    result.distance = sol;
    return result; 
}

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

std::optional<Intersection> Sphere::getFirstIntersection(Ray ray, float eps) const { 
    ray = ray.normalize();

    // vector from sphere center to ray origin
    glm::vec3 origin_to_center = ray.origin - position;

    // quadratic equation terms
    float a = glm::dot(ray.direction, ray.direction);
    float b = 2.f * glm::dot(ray.direction, origin_to_center);
    float c = glm::dot(origin_to_center, origin_to_center) - radius * radius;

    // find roots
    float discriminant = b * b - 4.f * a * c;

    // no intersection if negative
    if (discriminant < 0.f) return std::nullopt;

    // square root used in subsequent solution calculations
    float sqrt_discriminant = glm::sqrt(discriminant);
    float sol1 = (-b - sqrt_discriminant) / (2.f * a);
    float sol2 = (-b + sqrt_discriminant) / (2.f * a);

    // pick the nearest valid solution - the default is 
    // set to infinity (large float), if a valid solution
    // exists then it should get replaced.
    const float INFTY = 1e30f;
    float min_sol = INFTY;
    if (sol1 > eps && sol1 < min_sol) min_sol = sol1;
    if (sol2 > eps && sol2 < min_sol) min_sol = sol2;
    if (abs(min_sol - INFTY) < eps) return std::nullopt;

    // intersection found, return in result.
    Intersection result;
    result.position = ray.origin + min_sol * ray.direction;
    result.normal   = glm::normalize(result.position - position);
    result.distance = min_sol;
    return result;
}

/*
 * BONUS PART 1 - INFINITE AND CAPPED CYLINDERS
 * REFERENCE: https://davidjcobb.github.io/articles/ray-cylinder-intersection 
 * 
 * My implementations of both functions draws inspiration from the solutions for ray-cylinder
 * intersections by David Cobb to some extent. The page I linked above also explained the math
 * pretty thoroughly.
 * 
 */

std::optional<Intersection> InfiniteCylinder::getFirstIntersection(Ray ray, float eps) const {
    /*
     * Intersects an infinite cylinder.
     * Defined by:
     *   a. position
     *   b. axis direction
     *   c. radius
     * 
     * General strategy:
     *   1. Translate the ray origin to be relative to the cylinder base
     *   2. Use projections to set up a quadratic equation for the curved surface
     *   3. Solve it using the quadratic formula
     *   4. Use the closest valid root to compute the intersection point and normal
     * 
     * The math here is based directly on Cobb's derivation, especially how he sets up 
     * the a/b/c coefficients using dot products and projections. Structure-wise
     * it's quite different though - his algorithm was for a cylinder with end-caps
     * so it didn't track super well with an infinite cylinder. I kept variable names
     * identical to his where it made sense to make the math easier to follow.
     */
    
    ray = ray.normalize();
    // translate the ray origin to be relative to the cylinder base
    glm::vec3 Rl = ray.origin - position;
    // normalize the cylinder axis
    glm::vec3 Ca = glm::normalize(axis_direction);

    // compute dot products for use in quadratic coefficients (this follows cobbs math)
    float Ca_dot_Rd = glm::dot(Ca, ray.direction);
    float Ca_dot_Rl = glm::dot(Ca, Rl);
    float Rl_dot_Rl = glm::dot(Rl, Rl);

    // compute quadratic coefficients (this follows cobbs math)
    float a = 1.0f - Ca_dot_Rd * Ca_dot_Rd;
    float b = 2.0f * (glm::dot(ray.direction, Rl) - Ca_dot_Rd * Ca_dot_Rl);
    float c = Rl_dot_Rl - Ca_dot_Rl * Ca_dot_Rl - radius * radius;

    // compute discriminant and check for no intersection
    float discriminant = b * b - 4.0f * a * c;
    if (discriminant < 0.0f) return std::nullopt;

    // compute the roots using quadratic formula
    float sqrt_discriminant = glm::sqrt(discriminant);
    float sol1 = (-b - sqrt_discriminant) / (2.0f * a);
    float sol2 = (-b + sqrt_discriminant) / (2.0f * a);

    // pick the nearest valid solution - the default is 
    // set to infinity (large float), if a valid solution
    // exists then it should get replaced.
    const float INFTY = 1e30f;
    float min_sol = INFTY;
    if (sol1 > eps && sol1 < min_sol) min_sol = sol1;
    if (sol2 > eps && sol2 < min_sol) min_sol = sol2;
    if (abs(min_sol - INFTY) < eps) return std::nullopt;

    // compute intersection point and normal
    glm::vec3 hit_pos = ray.origin + min_sol * ray.direction;
    glm::vec3 hit_to_axis = hit_pos - position;
    glm::vec3 proj = glm::dot(hit_to_axis, Ca) * Ca;
    glm::vec3 normal = glm::normalize(hit_to_axis - proj);

    // return intersection result
    Intersection result;
    result.position = hit_pos;
    result.normal = normal;
    result.distance = min_sol;
    return result;
}



std::optional<Intersection> Cylinder::getFirstIntersection(Ray ray, float eps) const {
    /*
     * Intersects a finite cylinder with flat caps.
     * Defined by: 
     *   a. position
     *   b. axis direction
     *   c. radius and length
     * 
     * General strategy:
     *   1. Checks if the ray hits the curved side using a quadratic equation.
     *   2. Checks if the ray hits either cap using modified version of plane intersection.
     *   3. Returns the closest valid intersection (side or cap).
     * 
     * The implementation borrows math from Cobb's method, but I've had to adapt it here. 
     * I kept my variable names identical to the ones used in Cobbs implementation when
     * they made sense just so that the math was easier to follow.
     */

    ray = ray.normalize();
    glm::vec3 Ca = glm::normalize(axis_direction); // cylinder axis
    glm::vec3 Ct = position + length * Ca; // top center of the cylinder

    glm::vec3 Ro = ray.origin; // ray origin
    glm::vec3 Rd = ray.direction; // ray direction

    glm::vec3 Rl = Ro - position; // ray origin relative to base
    float Ca_dot_Rd = glm::dot(Ca, Rd); // projection of ray dir on axis
    float Ca_dot_Rl = glm::dot(Ca, Rl); // projection of relative origin on axis

    // Solves quadratic for intersection with side surface
    // Cobb's quadratic form: (* = dot product)
    // a = 1 - (Ca * Rd)^2
    // b = 2((Rd * Rl) - (Ca * Rd)(Ca * Rl))
    // c = (Rl * Rl) - (Ca * Rl)^2 - Cr^2
    float a = 1.f - Ca_dot_Rd * Ca_dot_Rd;
    float b = 2.f * (glm::dot(Rd, Rl) - Ca_dot_Rd * Ca_dot_Rl);
    float c = glm::dot(Rl, Rl) - Ca_dot_Rl * Ca_dot_Rl - radius * radius;

    // initialize min_sol to large float INFTY
    // if valid intersections were found the min_sol will be changed 
    // end up less than INFTY. 
    const float INFTY = 1e30f;
    float min_sol = INFTY;
    glm::vec3 best_position;
    glm::vec3 best_normal;

    // compute quadratic discriminant
    float discriminant = b * b - 4.f * a * c;

    // check for intersections with the curved side surface of the cylinder
    // 1. solve the quadratic equation for ray-cylinder intersection
    // 2. for each root t:
    //    a. it's in front of the ray origin (t > eps)
    //    b. the corresponding hit point falls within the cylinder's height bounds [0, length]
    // 3. compute the projected spine point (axis-aligned) at height Ho
    // 4. use that to compute the surface normal
    // 5. keep the smallest t and store its position + normal
    if (discriminant >= eps && glm::abs(a) > eps) {
        float sqrt_d = glm::sqrt(discriminant);
        float sol1 = (-b - sqrt_d) / (2.f * a);   // Hd = (-b +/- sqrt(disc)) / (2a)
        float sol2 = (-b + sqrt_d) / (2.f * a);

        for (float sol : {sol1, sol2}) {
            if (sol > eps && sol < min_sol) {
                glm::vec3 Hp = Ro + sol * Rd; // hit point on the cylinder surface -- Hp = Ro + Rd * Hd
                float Ho = glm::dot(Hp - position, Ca); // project a hit onto the axis

                if (Ho >= 0.f && Ho <= length) {
                    glm::vec3 Hs = position + Ho * Ca; // projection of hit onto cylinder axis - Cobb's math calls this Hs "hit spine position"
                    best_position = Hp;
                    best_normal = glm::normalize(Hp - Hs); // radial normal
                    min_sol = sol;
                }
            }
        }
    }

    // check for intersections with the flat end caps (both top and bottom)
    // 
    // Here, for each cap:
    // 1. compute intersection point with the cap's supporting plane
    // 2. check if that point lies within the cap's radius
    // 3. keep track of the closest valid one in min_sol
    for (int i = 0; i < 2; ++i) {
        glm::vec3 cap_center;
        glm::vec3 cap_normal;

        if (i == 0) {
            cap_center = position;  // bottom cap
            cap_normal = -Ca;
        } else {
            cap_center = Ct;        // top cap
            cap_normal = Ca;
        }

        float denom = glm::dot(Rd, cap_normal);
        if (glm::abs(denom) > eps) {
            float t = glm::dot(cap_center - Ro, cap_normal) / denom;
            if (t > eps && t < min_sol) { // needs to be greater than the error term and less than the spine t
                glm::vec3 Hp = Ro + t * Rd;
                glm::vec3 Dd = Hp - cap_center;

                if (glm::dot(Dd, Dd) <= radius * radius) {
                    best_position = Hp;
                    best_normal = cap_normal;
                    min_sol = t;
                }
            }
        }
    }

    // Return closest valid hit, or none if nothing intersected
    if (min_sol < INFTY) {
        return Intersection{best_position, best_normal, min_sol};
    }

    return std::nullopt;
}
