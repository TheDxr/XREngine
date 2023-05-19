#pragma once
#define GLFW_INCLUDE_NONE
#include <memory>

#include "OpenGL/Application.h"
#include "OpenGL/InputSystem.h"
#include "OpenGL/Shader.h"
#include "Components/Camera.h"

#include "Common/Light/LightDirectional.h"
#include "Common/Light/LightPoint.h"
#include "Common/Model/Model.h"

#include "UI/IGUI.h"

class DxrApplication : public Application
{
public:
	DxrApplication();
	~DxrApplication() override = default;
	static DxrApplication& GetInstance();
    std::unique_ptr<Camera> pCamera;
	std::unique_ptr<InputSystem> pInputSystem;
    std::unique_ptr<IGUI> pGUI;

    std::shared_ptr<LightDirectional> pLightDirectional;
    std::shared_ptr<LightPoint> pLightPoint;
    std::vector<std::shared_ptr<Entity>> models;
protected:
	void Update() override;
    void RenderSkybox();
    void RenderBasic(const std::vector<std::shared_ptr<Entity>>& entities);
    void RenderModels();
private:
	static void ProcessInputCallback(int key);
	static void MouseCallback(GLFWwindow* window, double xpos, double ypos);

	ShaderProgram entityShader;
	ShaderProgram baseShader;
};
