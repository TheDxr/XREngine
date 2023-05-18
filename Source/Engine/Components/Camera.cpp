#include <glm/glm.hpp>

#include "Camera.h"

using namespace glm;

Camera::Camera(glm::vec3 position, float pitch, float yaw):
    Position(position), Pitch(pitch), Yaw(yaw)
{
    Forward.x = glm::cos(glm::radians(Pitch)) * glm::cos(glm::radians(Yaw));
    Forward.y = glm::sin(glm::radians(Pitch));
    Forward.z = glm::cos(glm::radians(Pitch)) * glm::sin(glm::radians(Yaw));
    Forward = glm::normalize(Forward);
}

glm::mat4 Camera::GetViewMat()
{
    glm::mat4 viewMat{1.0f};
    Forward = normalize(Forward);
    vec3 Right   = normalize(cross(Forward, vec3(0.0f, 1.0f, 0.0f)));
    vec3 Up      = normalize(cross(Right, Forward));

    viewMat[0][0] = Right.x;
    viewMat[1][0] = Right.y;
    viewMat[2][0] = Right.z;

    viewMat[0][1] = Up.x;
    viewMat[1][1] = Up.y;
    viewMat[2][1] = Up.z;

    viewMat[0][2] = -Forward.x;
    viewMat[1][2] = -Forward.y;
    viewMat[2][2] = -Forward.z;

    viewMat[3][0] = -dot(Right, Position);
    viewMat[3][1] = -dot(Up, Position);
    viewMat[3][2] = dot(Forward, Position);

    // viewMat = viewMat * Math::CreateTranslationMatrix(-transform.Position);;
    return viewMat;
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY, float speed)
{
    deltaX *= speed;
    deltaY *= speed;
    Yaw += deltaX;
    Pitch += deltaY;
    if(Pitch > 89.f)
        Pitch = 89.f;
    if(Pitch < -89.f)
        Pitch = -89.f;
    Forward.x = glm::cos(glm::radians(Pitch)) * glm::cos(glm::radians(Yaw));
    Forward.y = glm::sin(glm::radians(Pitch));
    Forward.z = glm::cos(glm::radians(Pitch)) * glm::sin(glm::radians(Yaw));
    Forward = glm::normalize(Forward);
}
void Camera::Update(glm::vec3 deltaPos) { Position += deltaPos;}
glm::mat4 Camera::GetProjectionMat() {
    return glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    //glm::perspective(glm::radians(45.0), 1.0, 0.1, 100.0)
}
