#pragma once
#include <glm/glm.hpp>

#include "Materials.h"
#include "Shapes.h"
#include <memory>

struct Object{
    Object(std::shared_ptr<Shape> init_shape = nullptr, Material init_material = Material())
        : shape(init_shape)
        , material(init_material)
    {
    }

    std::shared_ptr<Shape> shape;
    Material material;
};
