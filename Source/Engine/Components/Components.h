#pragma once
#include <glm/glm.hpp>
#include "Camera.h"
#include "Transform.h"

struct Gravity {
    glm::vec3 Force;
};

struct RigidBody {
    glm::vec3 Velocity;
    glm::vec3 Acceleration;
};



struct LightDirectional
{
	glm::vec3 Color;
	glm::vec3 Angle;
	glm::vec3 Direction;
};

struct LightPoint
{
    glm::vec3 Angle;
    glm::vec3 Color;
    glm::vec3 Direction;
    // 衰减系数
    const float CONSTANT = 1.0f;
    const float LINEAR = 0.09f;
    const float QUADRATIC = 0.032f;
};

