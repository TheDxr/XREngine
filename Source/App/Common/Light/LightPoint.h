#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "../Entity.h"

class LightPoint : public Entity
{
public:
    LightPoint(glm::vec3 position, glm::vec3 angle = glm::vec3(0.0f), glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
    ~LightPoint() = default;
    glm::vec3 Position;
    glm::vec3 Angle;
    glm::vec3 Color;
    glm::vec3 Direction;
    // 衰减系数
    static constexpr float Constant  = 1.0f;
    static constexpr float Linear    = 0.09f;
    static constexpr float Quadratic = 0.032f;

    void Update();
};
