#include "LightSpot.h"

#include <glm/gtx/rotate_vector.hpp>

LightSpot::LightSpot(glm::vec3 position, glm::vec3 angle, glm::vec3 color) :
    Position(position), Angle(angle), Color(color)
{
    Direction = glm::vec3(0.0f, 0.0f, 1.0f);
}

void LightSpot::updateDirection()
{
    Direction = glm::vec3(0.0f, 0.0f, 1.0f);
    Direction = glm::rotateX(Direction, Angle.x);
    Direction = glm::rotateY(Direction, Angle.y);
    Direction = glm::rotateZ(Direction, Angle.z);
    Direction = -glm::normalize(Direction);
}
