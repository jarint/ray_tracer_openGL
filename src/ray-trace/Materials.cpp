#include "Materials.h"

glm::vec3 PhongProperties::Ia(const glm::vec3 &lc) const { return lc * ambient_strength * colour; }

glm::vec3 PhongProperties::Id(const glm::vec3 &lc, const glm::vec3 &ld, const glm::vec3 &sn) const
{
    float ld_dot_sn     = glm::dot(ld, sn);
    float ld_dot_sn_max = glm::max(0.0f, ld_dot_sn);
    return lc * diffuse_strength * ld_dot_sn_max * colour;
}

glm::vec3 PhongProperties::Is(const glm::vec3 &lc, const glm::vec3 &ld, const glm::vec3 &vd, const glm::vec3 &sn) const
{
    glm::vec3 lrd              = -glm::reflect(ld, sn);
    float lrd_dot_vd           = glm::dot(lrd, vd);
    float lrd_dot_vd_max       = glm::max(0.0f, lrd_dot_vd);
    float lrd_dot_vd_max_power = std::pow(lrd_dot_vd_max, shininess);
    return lc * specular_strength * lrd_dot_vd_max_power;
}
