#pragma once

#include <glm/glm.hpp>
#include <string>
#include "Transform.h"

struct Camera
{
    glm::vec3 position;
    glm::vec3 forward;
    float pitch;
    float yaw;
    Camera() = default;
    Camera(glm::vec3 position, float pitch, float yaw);
    glm::mat4 getViewMat();
    glm::mat4 getProjectionMat();

    void processMouseMovement(float deltaX, float deltaY, float speed);
    void update(glm::vec3 deltaPos) { position += deltaPos; }
};

// 围着中心点拍
// float theta = 0.0f;
// transform.Rotation = rotate(transform.Rotation,radians(0.01f),vec3(0.0f,1.0f,0.0f));
// transform.Position.x = 2.0*cos(radians(theta) - 3.1415926/2.0);
// transform.Position.z = 2.0*sin(radians(theta) - 3.1415926/2.0);
// theta+=0.01;
