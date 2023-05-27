#include "LightPoint.h"

LightPoint::LightPoint(glm::vec3 position, glm::vec3 angle, glm::vec3 color) :
    Position(position), Angle(angle), Color(color)
{
    Direction = glm::vec3(0.0f, 0.0f, 1.0f);

}

void LightPoint::updateDirection()
{
}
