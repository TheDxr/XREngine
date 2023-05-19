#pragma once

#include "Texture.h"

struct Material
{
    Material() = default;
    Material(Texture &diffuse, Texture &specular, Texture &normal, Texture &height) :
        Diffuse(diffuse), Specular(specular), Normal(normal), Height(height)
    {}
    Texture Diffuse;
    Texture Specular;
    Texture Normal;
    Texture Height;
    float Shininess = 32.0f;
    glm::vec3 RawColor{1.0f, 1.0f, 1.0f};
};

