#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

struct Transform
{
	glm::vec3 Position{0.0f};
	glm::qua<float> Rotation{0.0f,0.0f,0.0f,1.0f};
    glm::vec3 Scale{1.0f,1.0f,1.0f};
};
