#include "Application.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <glad/glad.h>
#include <glm/ext/matrix_transform.hpp>
#include <memory>
#include <spdlog/spdlog.h>

#include "Common/Camera.h"
#include "Common/Light/LightDirectional.h"
#include "Common/Light/LightPoint.h"
#include "Model/Model.h"
#include "Timer.h"
// #include "Common/Model/Model.h"
// #include "UI/EmbeddedUI.h"
#include "glError.h"

namespace dxr::gl
{
using namespace std;
using namespace glm;
std::unique_ptr<Camera> pCamera;

std::shared_ptr<LightDirectional> pLightDirectional;
std::shared_ptr<LightPoint> pLightPoint;
std::vector<std::shared_ptr<Model>> models;
void MouseCallback(GLFWwindow *window, double xpos, double ypos);

Application::Application(int width, int height, int posX, int posY, const std::string &title)
: window(width, height, title)
{

#pragma region 设置全局属性
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS);    // depth-testing interprets a smaller value as "closer"

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSetInputMode(window.getHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    // glfwSwapInterval(GLFW_TRUE); // vsync
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 线框模式
    glfwSetCursorPosCallback(window.getHandle(), (GLFWcursorposfun) MouseCallback);
    entityShader = std::make_unique<ShaderProgram>("Shaders/Entity.vert", "Shaders/Entity.frag");
    baseShader   = std::make_unique<ShaderProgram>("Shaders/Basic.vert", "Shaders/Basic.frag");

    glCheckError(__FILE__, __LINE__);
#pragma endregion

#pragma region 创建实体
    pCamera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 5.0f), -15.0f, -90.0f);
    //
    pLightDirectional = std::make_shared<LightDirectional>(
        glm::vec3(0.0f, 12.0f, 5.0f),
        glm::vec3(glm::radians(90.0f), 0.0f, glm::radians(45.0f)),
        glm::vec3(0.9f, 0.9f, 1.0f));
    pLightPoint = std::make_shared<LightPoint>(glm::vec3(1.0f, 8.0f, 3.0f));

    models.emplace_back(
        std::make_shared<Model>("D:/SourceCode/CppCode/Dxr3DEngine/Assets/test/utah-teapot.obj"));
    //    models[0]->SetPosition(glm::vec3(0.0f, 2.3f, -2.0f));
    models.emplace_back(
        std::make_shared<Model>("D:/SourceCode/CppCode/Dxr3DEngine/Assets/nanosuit/nanosuit.obj"));
       // models.emplace_back(std::make_shared<Model>("D:/SourceCode/CppCode/OpenGL/Assets/test/test.obj"));

#pragma endregion

#pragma region 设置 uniform
    entityShader->use();
    entityShader->setUniform("dirLight.direction", pLightDirectional->Direction);
    entityShader->setUniform("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    entityShader->setUniform("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    entityShader->setUniform("dirLight.specular", 0.5f, 0.5f, 0.5f);

    entityShader->setUniform("pointLight.position", pLightPoint->Position);
    entityShader->setUniform("pointLight.ambient", 0.05f, 0.05f, 0.05f);
    entityShader->setUniform("pointLight.diffuse", 0.8f, 0.8f, 0.8f);
    entityShader->setUniform("pointLight.specular", 1.0f, 1.0f, 1.0f);
    entityShader->setUniform("pointLight.constant", pLightPoint->Constant);
    entityShader->setUniform("pointLight.linear", pLightPoint->Linear);
    entityShader->setUniform("pointLight.quadratic", pLightPoint->Quadratic);
    entityShader->unuse();
#pragma endregion
}


void Application::run()
{
    // Make the window's context current
    glfwMakeContextCurrent(window.getHandle());

    while(!glfwWindowShouldClose(window.getHandle())) {
        processInput();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //      Timer::preUpdate();
//        entityShader->use();
//        while(Timer::getAccumulator() >= Timer::getFixedDeltaTime()) {
//            Timer::fixedUpdate();
//            // ECS_Engine->FixedUpdate(Timer::FixedDeltaTime().count());
//            /*cubeTransform.Rotate(1.0f, 1.0f, 1.0f);
//            cube2Transform.Rotate(1.0f, 0.0f, 0.0f);
//            cube3Transform.Rotate(0.5f, 0.5f, 0.0f);
//            cube4Transform.Rotate(0.0f, 0.5f, 2.0f);*/
//        }
//        // ECS_Engine->Update(Timer::DeltaTime().count());
//
//        // detech window related changes
//        window.detectWindowDimensionChange();

        // execute the frame code
        update();

        // Swap Front and Back buffers (double buffering)
        glfwSwapBuffers(window.getHandle());
        // Pool and process events
        glfwPollEvents();
    }

    glfwTerminate();
}


void Application::update()
{
    entityShader->use();
    entityShader->setUniform("cameraPos", pCamera->position);
    glm:mat4 modelMat = glm::mat4(1.0f);
    entityShader->setUniform("modelMat", modelMat);
    entityShader->setUniform("viewMat", pCamera->getViewMat());
    entityShader->setUniform("projMat", pCamera->getProjectionMat());
    for(auto &model : models) {
        model->draw(*entityShader);
    }
}



bool firstMouse = true;
 double lastX    = 0.0f;
 double lastY    = 0.0f;
 void MouseCallback(GLFWwindow *window, double xpos, double ypos)
{
    if(pCamera == nullptr) return;
    if(firstMouse) {
        lastX      = xpos;
        lastY      = ypos;
        firstMouse = false;
    }
    auto dx = static_cast<float>(xpos - lastX);
    auto dy = static_cast<float>(lastY - ypos);
    pCamera->processMouseMovement(dx, dy, 0.05);
    lastX = xpos;
    lastY = ypos;
}

// void Application::RenderBasic(const std::vector<std::shared_ptr<Entity>> &entities)
//{
//    baseShader.use();
//    for(auto &entity : entities) {
//        baseShader.setUniform("viewMat", pCamera->GetViewMat());
//        baseShader.setUniform("projMat", pCamera->GetProjectionMat());
//        baseShader.setUniform("modelMat", entity->GetModelMat());
//        baseShader.setUniform("objRawColor", vec3(0.5f, 1.0f, 0.0f));
//        entity->Render(baseShader);
//    }
//    baseShader.unuse();
//}
// void Application::RenderModels()
//{
//    for(auto model : models) {
//        glm::mat4 modelMat(1.0f);
//        modelMat = glm::translate(modelMat, model->GetPosition());
//        entityShader.setUniform("modelMat", modelMat);
//        model->Render(entityShader);
//    }
//}
// void Application::RenderSkybox()
//{
////        skyboxShader.use();
////        skyboxShader.setUniform("viewMat",
////        glm::mat4(glm::mat3(pCamera->GetViewMat())));
////        skyboxShader.setUniform("projMat", pCamera->GetProjectionMat());
////        skyboxShader.setUniform("skybox", 0);
////        skybox->Render(skyboxShader);
////        skyboxShader.unuse();
//}
void Application::processInput()
{
    if(pCamera == nullptr) return;
    if(glfwGetKey(window.getHandle(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window.getHandle(), true);
    float cameraSpeed = 0.0025f ;//* getFrameDeltaTime();
    if(glfwGetKey(window.getHandle(), GLFW_KEY_LEFT_SHIFT)) cameraSpeed *= 8.0f;
    if(glfwGetKey(window.getHandle(), GLFW_KEY_E))
        pCamera->update(glm::vec3(0.0f, cameraSpeed, 0.0f));
    if(glfwGetKey(window.getHandle(), GLFW_KEY_SPACE))
        pCamera->update(glm::vec3(0.0f, cameraSpeed, 0.0f));
    if(glfwGetKey(window.getHandle(), GLFW_KEY_LEFT_CONTROL))
        pCamera->update(glm::vec3(0.0f, -cameraSpeed, 0.0f));
    if(glfwGetKey(window.getHandle(), GLFW_KEY_Q))
        pCamera->update(glm::vec3(0.0f, -cameraSpeed, 0.0f));
    if(glfwGetKey(window.getHandle(), GLFW_KEY_W))
        pCamera->update(cameraSpeed * pCamera->forward);
    if(glfwGetKey(window.getHandle(), GLFW_KEY_S))
        pCamera->update(-cameraSpeed * pCamera->forward);
    if(glfwGetKey(window.getHandle(), GLFW_KEY_A))
        pCamera->update(
            -glm::normalize(glm::cross(pCamera->forward, vec3(.0, 1., .0))) *
            cameraSpeed);
    if(glfwGetKey(window.getHandle(), GLFW_KEY_D))
        pCamera->update(
            glm::normalize(glm::cross(pCamera->forward, vec3(.0, 1., .0))) *
            cameraSpeed);
}

} // namespace dxr::gl
