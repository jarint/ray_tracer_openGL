#pragma once

#include <optional>

#include <glm/glm.hpp>

#include "Lights.h"

struct Properties {
    Properties(float init_weight = 1.f)
        : weight(init_weight)
    {
    }
    float weight;
};

struct PhongProperties : public Properties {
    PhongProperties(
        float init_weight            = 1.f,
        glm::vec3 init_colour        = {1.0f, 1.0f, 1.0f},
        float init_ambient_strength  = 0.1f,
        float init_diffuse_strength  = 0.6f,
        float init_specular_strength = 0.9f,
        float init_shininess         = 32.0f
    )
        : Properties(init_weight)
        , colour(init_colour)
        , ambient_strength(init_ambient_strength)
        , diffuse_strength(init_diffuse_strength)
        , specular_strength(init_specular_strength)
        , shininess(init_shininess)
    {
    }
    glm::vec3 colour;  // Object Colour
    float ambient_strength;  // Ambient strength
    float diffuse_strength;  // Diffuse strength
    float specular_strength;  // Specular strength
    float shininess;  // Specular Exponent

    glm::vec3 Ia(const glm::vec3 &lc) const;
    glm::vec3 Id(const glm::vec3 &lc, const glm::vec3 &ld, const glm::vec3 &sn) const;
    glm::vec3 Is(const glm::vec3 &lc, const glm::vec3 &ld, const glm::vec3 &vd, const glm::vec3 &sn) const;
};

struct MirrorProperties : public Properties {
    MirrorProperties(float init_weight = 1.f)
        : Properties(init_weight)
    {
    }
};

struct FresnelProperties : public Properties {
    FresnelProperties(float init_weight = 1.f, float init_refraction_index = 1.5f)
        : Properties(init_weight)
        , refraction_index(init_refraction_index)
    {
    }

    // Material index (used for snell law + frenel effect + TIR)
    float refraction_index;  // Air is ~1, water is ~1.33, glass is ~1.5
};

struct Material {
    Material(PhongProperties init_phong_properties = PhongProperties())
        : phong_properties(init_phong_properties)
        , mirror_properties(std::nullopt)
        , fresnel_properties(std::nullopt)
    {
    }

    Material(MirrorProperties init_mirror_properties, PhongProperties init_phong_properties = PhongProperties())
        : phong_properties(init_phong_properties)
        , mirror_properties(init_mirror_properties)
        , fresnel_properties(std::nullopt)
    {
    }

    Material(FresnelProperties init_fresnel_properties, PhongProperties init_phong_properties = PhongProperties())
        : phong_properties(init_phong_properties)
        , mirror_properties(std::nullopt)
        , fresnel_properties(init_fresnel_properties)
    {
    }

    Material(
        PhongProperties init_phong_properties, MirrorProperties init_mirror_properties,
        FresnelProperties init_fresnel_properties
    )
        : phong_properties(init_phong_properties)
        , mirror_properties(init_mirror_properties)
        , fresnel_properties(init_fresnel_properties)
    {
    }

    bool hasMirrorProperties() const { return mirror_properties.has_value(); }
    bool hasFresnelProperties() const { return fresnel_properties.has_value(); }

    // Note if mirror / frenel properties are not present (or level == 0), 100% phong is used
    PhongProperties phong_properties; 
    std::optional<MirrorProperties> mirror_properties;
    std::optional<FresnelProperties> fresnel_properties;
};
