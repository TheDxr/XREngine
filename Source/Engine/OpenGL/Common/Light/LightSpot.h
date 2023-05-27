#pragma once
#include <glm/vec3.hpp>

class LightSpot
{
    LightSpot(glm::vec3 position, glm::vec3 angle, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
    glm::vec3 Position;
    glm::vec3 Angle;
    glm::vec3 Color;
    glm::vec3 Direction;
    // 衰减系数
    const float Constant  = 1.0f;
    const float Linear    = 0.09f;
    const float Quadratic = 0.032f;

    void updateDirection();
};
