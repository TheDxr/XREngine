#pragma once

#include "Texture.h"
namespace dxr::gl
{
struct Material
{
    Material() = default;
    Material(Texture &diffuse, Texture &specular, Texture &normal, Texture &height)
        : diffuse(diffuse), specular(specular), normal(normal), height(height)
    {}
    Texture diffuse;
    Texture specular;
    Texture normal;
    Texture height;
    float shininess = 32.0f;
    glm::vec3 rawColor{1.0f, 1.0f, 1.0f};
};
} // namespace dxr::gl
