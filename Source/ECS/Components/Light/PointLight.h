#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

struct PointLight
{

    glm::vec3 Position;
    glm::vec3 Angle;
    glm::vec3 Color;
    glm::vec3 Direction;
    // 衰减系数
    static constexpr float Constant  = 1.0f;
    static constexpr float Linear    = 0.09f;
    static constexpr float Quadratic = 0.032f;
    //#include "LightPoint.h"
    //
    //LightPoint::LightPoint(glm::vec3 position, glm::vec3 angle, glm::vec3 color) :
    //    Position(position), Angle(angle), Color(color)
    //{
    //    mTransform.Position = position;
    //    Direction = glm::vec3(0.0f, 0.0f, 1.0f);
    //}
    //
    //void LightPoint::Update() {}
};
