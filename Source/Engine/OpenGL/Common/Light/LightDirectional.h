#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
class LightDirectional
{
public:
    LightDirectional(glm::vec3 position, glm::vec3 angle, glm::vec3 color);
	~LightDirectional() = default;
	glm::vec3 Position;
	glm::vec3 Color;
	glm::vec3 Angle;
	glm::vec3 Direction;

	void updateDirection();
};
