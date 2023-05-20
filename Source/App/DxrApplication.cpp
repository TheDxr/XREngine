#include "DxrApplication.h"
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <functional>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <memory>

#include "Components/Camera.h"
#include "Common/Light/LightDirectional.h"
#include "Common/Utils.h"

#include "UI/EmbeddedUI.h"
#include "OpenGL/glError.h"

using namespace std;
using namespace glm;


DxrApplication &DxrApplication::GetInstance()
{
    static DxrApplication instance;
    return instance;
}

DxrApplication::DxrApplication() :
    Application(800, 800, 800, 200),
    entityShader("Shaders/Entity.vert", "Shaders/Entity.frag"),
    baseShader("Shaders/Basic.vert", "Shaders/Basic.frag")
{
#pragma region 设置全局属性
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LEQUAL);  // depth-testing interprets a smaller value as "closer"

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    // glfwSwapInterval(GLFW_TRUE); // vsync
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 线框模式
    pInputSystem = std::make_unique<InputSystem>(GetWindow());
    pInputSystem->DisableCursor();
    pInputSystem->SetGlfwCursorPosCallback(MouseCallback);
    pGUI = std::make_unique<EmbeddedUI>(GetWindow());
    pGUI->Init();
    glCheckError(__FILE__, __LINE__);
#pragma endregion
#pragma region 创建实体
    pCamera = std::make_unique<Camera>(glm::vec3(0.0f, 10.0f, 10.0f), -15.0f, -90.0f);

    pLightDirectional = std::make_shared<LightDirectional>(glm::vec3(0.0f, 12.0f, 5.0f),
                                                           glm::vec3(glm::radians(90.0f), 0.0f, glm::radians(45.0f)),
                                                           glm::vec3(0.9f, 0.9f, 1.0f));
    pLightPoint       = std::make_shared<LightPoint>(glm::vec3(1.0f, 8.0f, 3.0f));

    models.emplace_back(std::make_shared<Model>("D:/SourceCode/CppCode/Dxr3DEngine/Assets/test/utah-teapot.obj"));
    models[0]->SetPosition(glm::vec3(0.0f, 2.3f, -2.0f));
    models.emplace_back(std::make_shared<Model>("D:/SourceCode/CppCode/Dxr3DEngine/Assets/nanosuit/nanosuit.obj"));
    // models.emplace_back(std::make_shared<Model>("D:/SourceCode/CppCode/OpenGL/Assets/test/test.obj"));

#pragma endregion

#pragma region 设置 uniform
    entityShader.Use();
    entityShader.SetUniform("dirLight.direction", pLightDirectional->Direction);
    entityShader.SetUniform("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    entityShader.SetUniform("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    entityShader.SetUniform("dirLight.specular", 0.5f, 0.5f, 0.5f);

    entityShader.SetUniform("pointLight.position", pLightPoint->Position);
    entityShader.SetUniform("pointLight.ambient", 0.05f, 0.05f, 0.05f);
    entityShader.SetUniform("pointLight.diffuse", 0.8f, 0.8f, 0.8f);
    entityShader.SetUniform("pointLight.specular", 1.0f, 1.0f, 1.0f);
    entityShader.SetUniform("pointLight.constant", pLightPoint->Constant);
    entityShader.SetUniform("pointLight.linear", pLightPoint->Linear);
    entityShader.SetUniform("pointLight.quadratic", pLightPoint->Quadratic);

#pragma endregion
}


void DxrApplication::Update()
{
    pInputSystem->ProcessKeyInput(ProcessInputCallback);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#pragma region 渲染场景
    entityShader.Use();
    entityShader.SetUniform("cameraPos", pCamera->Position);
    entityShader.SetUniform("viewMat", pCamera->GetViewMat());
    entityShader.SetUniform("projMat", pCamera->GetProjectionMat());
    Transform transform;
    transform.Position.y = 8.0f;
    transform.Position.x = 3.0f * sin(glfwGetTime());
    transform.Position.z = 3.0f * cos(glfwGetTime());
    pLightPoint->SetTransform(transform);
    entityShader.SetUniform("pointLight.position", transform.Position);

    RenderModels();

    entityShader.Unuse();
#pragma endregion

    // 渲染实体
    RenderBasic({pLightPoint, pLightDirectional});
}


bool firstMouse = true;
double lastX    = 0.0f;
double lastY    = 0.0f;
void DxrApplication::MouseCallback(GLFWwindow *window, double xpos, double ypos)
{
    if(firstMouse) {
        lastX      = xpos;
        lastY      = ypos;
        firstMouse = false;
    }
    auto dx = static_cast<float>(xpos - lastX);
    auto dy = static_cast<float>(lastY - ypos);
    DxrApplication::GetInstance().pCamera->ProcessMouseMovement(dx, dy, 0.05);
    lastX = xpos;
    lastY = ypos;
}

void DxrApplication::ProcessInputCallback(int key)
{
    if(DxrApplication::GetInstance().pCamera == nullptr)
        return;
    auto &pCamera     = DxrApplication::GetInstance().pCamera;
    float cameraSpeed = 2.5f * DxrApplication::GetInstance().GetFrameDeltaTime();
    if(glfwGetKey(DxrApplication::GetInstance().GetWindow(), GLFW_KEY_LEFT_SHIFT))
        cameraSpeed *= 8.0f;
    switch(key) {
    case GLFW_KEY_E:
        pCamera->Update(glm::vec3(0.0f, cameraSpeed, 0.0f));
        break;
    case GLFW_KEY_SPACE:
        pCamera->Update(glm::vec3(0.0f, cameraSpeed, 0.0f));
        break;
    case GLFW_KEY_LEFT_CONTROL:
        pCamera->Update(glm::vec3(0.0f, -cameraSpeed, 0.0f));
        break;
    case GLFW_KEY_Q:
        pCamera->Update(glm::vec3(0.0f, -cameraSpeed, 0.0f));
        break;
    case GLFW_KEY_W:
        pCamera->Update(cameraSpeed * pCamera->Forward);
        break;
    case GLFW_KEY_S:
        pCamera->Update(-cameraSpeed * pCamera->Forward);
        break;
    case GLFW_KEY_A:
        pCamera->Update(-glm::normalize(glm::cross(pCamera->Forward, vec3(.0, 1., .0))) * cameraSpeed);
        break;
    case GLFW_KEY_D:
        pCamera->Update(glm::normalize(glm::cross(pCamera->Forward, vec3(.0, 1., .0))) * cameraSpeed);
        break;
    default:
        break;
    }
}
void DxrApplication::RenderBasic(const std::vector<std::shared_ptr<Entity>> &entities)
{
    baseShader.Use();
    for(auto &entity : entities) {
        baseShader.SetUniform("viewMat", pCamera->GetViewMat());
        baseShader.SetUniform("projMat", pCamera->GetProjectionMat());
        baseShader.SetUniform("modelMat", entity->GetModelMat());
        baseShader.SetUniform("objRawColor", vec3(0.5f, 1.0f, 0.0f));
        entity->Render(baseShader);
    }
    baseShader.Unuse();
}
void DxrApplication::RenderModels()
{
    for(auto model : models) {
        glm::mat4 modelMat(1.0f);
        modelMat = glm::translate(modelMat, model->GetPosition());
        entityShader.SetUniform("modelMat", modelMat);
        model->Render(entityShader);
    }
}
void DxrApplication::RenderSkybox()
{
    //    skyboxShader.Use();
    //    skyboxShader.SetUniform("viewMat", glm::mat4(glm::mat3(pCamera->GetViewMat())));
    //    skyboxShader.SetUniform("projMat", pCamera->GetProjectionMat());
    //    skyboxShader.SetUniform("skybox", 0);
    //    skybox->Render(skyboxShader);
    //    skyboxShader.Unuse();
}
