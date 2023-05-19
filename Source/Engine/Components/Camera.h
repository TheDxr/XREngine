#pragma once

#include <string>
#include <glm/glm.hpp>
#include "Transform.h"

struct Camera
{
    glm::vec3 Position;
    glm::vec3 Forward{};
	float Pitch;
	float Yaw;
    void ProcessMouseMovement(float deltaX, float deltaY, float speed);
    void Update(glm::vec3 deltaPos);
    Camera(glm::vec3 position, float pitch, float yaw);
	void Update(Transform& transform)
	{
		// Forward.x = Math::Cos(Math::ToRadians(Pitch)) * Math::Cos(Math::ToRadians(Yaw));
		// Forward.y = Math::Sin(Math::ToRadians(Pitch));
		// Forward.z = Math::Cos(Math::ToRadians(Pitch)) * Math::Sin(Math::ToRadians(Yaw));
		//auto tfMat = Math::CreateTransformationMatrix(transform.Position,transform.Rotation,Vec3(1.0f));
	}
    glm::mat4 GetProjectionMat();
    glm::mat4 GetViewMat();
};

// 围着中心点拍
// float theta = 0.0f;
// transform.Rotation = rotate(transform.Rotation,radians(0.01f),vec3(0.0f,1.0f,0.0f));
// transform.Position.x = 2.0*cos(radians(theta) - 3.1415926/2.0);
// transform.Position.z = 2.0*sin(radians(theta) - 3.1415926/2.0);
// theta+=0.01;
