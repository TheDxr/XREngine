#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

struct Transform
{
	glm::vec3 position{0.0f};
	glm::qua<float> rotation{0.0f,0.0f,0.0f,1.0f};
    glm::vec3 scale{1.0f,1.0f,1.0f};
};
