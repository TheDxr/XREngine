#pragma once
#include <glm/vec3.hpp>

struct SpotLight
{
    SpotLight() = default;
    glm::vec3 Position;
    glm::vec3 Angle;
    glm::vec3 Color = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 Direction;
    // 衰减系数
    const float Constant  = 1.0f;
    const float Linear    = 0.09f;
    const float Quadratic = 0.032f;

   // void updateDirection();

    //LightSpot::LightSpot(glm::vec3 position, glm::vec3 angle, glm::vec3 color) :
    //    Position(position), Angle(angle), Color(color)
    //{
    //    Direction = glm::vec3(0.0f, 0.0f, 1.0f);
    //}
    //
    //void LightSpot::updateDirection()
    //{
    //    Direction = glm::vec3(0.0f, 0.0f, 1.0f);
    //    Direction = glm::rotateX(Direction, Angle.x);
    //    Direction = glm::rotateY(Direction, Angle.y);
    //    Direction = glm::rotateZ(Direction, Angle.z);
    //    Direction = -glm::normalize(Direction);
    //}

};
