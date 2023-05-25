#include "Camera.h"

#include <glm/glm.hpp>


using namespace glm;
void Camera::processMouseMovement(float deltaX, float deltaY, float speed)
{
    deltaX *= speed;
    deltaY *= speed;
    yaw += deltaX;
    pitch += deltaY;
    if(pitch > 89.f) pitch = 89.f;
    if(pitch < -89.f) pitch = -89.f;
    forward.x = glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(yaw));
    forward.y = glm::sin(glm::radians(pitch));
    forward.z = glm::cos(glm::radians(pitch)) * glm::sin(glm::radians(yaw));
    forward   = glm::normalize(forward);
}
glm::mat4 Camera::getViewMat()
{
    glm::mat4 viewMat{1.0f};
    forward         = normalize(forward);
    glm::vec3 Right = normalize(cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
    glm::vec3 Up    = normalize(cross(Right, forward));

    viewMat[0][0] = Right.x;
    viewMat[1][0] = Right.y;
    viewMat[2][0] = Right.z;

    viewMat[0][1] = Up.x;
    viewMat[1][1] = Up.y;
    viewMat[2][1] = Up.z;

    viewMat[0][2] = -forward.x;
    viewMat[1][2] = -forward.y;
    viewMat[2][2] = -forward.z;

    viewMat[3][0] = -dot(Right, position);
    viewMat[3][1] = -dot(Up, position);
    viewMat[3][2] = dot(forward, position);

    // viewMat = viewMat * Math::CreateTranslationMatrix(-transform.Position);;
    return viewMat;
}
Camera::Camera(glm::vec3 position, float pitch, float yaw)
    : position(position), pitch(pitch), yaw(yaw)
{
    forward.x = glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(yaw));
    forward.y = glm::sin(glm::radians(pitch));
    forward.z = glm::cos(glm::radians(pitch)) * glm::sin(glm::radians(yaw));
    forward   = glm::normalize(forward);
}
glm::mat4 Camera::getProjectionMat()
{
    return glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    // glm::perspective(glm::radians(45.0), 1.0, 0.1, 100.0)
}

