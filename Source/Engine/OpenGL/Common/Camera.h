#pragma once
#include <glm/glm.hpp>
#include <string>

class Camera 
{
public:
    Camera(glm::vec3 position, glm::vec3 forward);
	Camera(glm::vec3 position, float pitch, float yaw);
	~Camera() = default;
	Camera& operator=(const Camera& cam) = delete;
	Camera (const Camera& cam) = delete;
	Camera&& operator=(const Camera&& cam) = delete;
	Camera(const Camera&& cam) = delete;

    void processMouseMovement(float deltaX, float deltaY, float speed);
    void update(glm::vec3 deltaPos) { position += deltaPos; }

	glm::mat4 getViewMat();
    glm::mat4 getProjectionMat();
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
	float pitch;
	float yaw;
};
