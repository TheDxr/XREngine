#include "Application.h"

#include <glad/glad.h>
#include <iostream>
#include <stdexcept>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <memory>
#include <spdlog/spdlog.h>

#include "Timer.h"
// #include "Common/Model/Model.h"
// #include "UI/EmbeddedUI.h"
#include "glError.h"

namespace dxr::gl
{
using namespace std;
using namespace glm;

Application::Application(int width, int height, int posX, int posY, const std::string &title)
    : window(width, height, title), entityShader("Shaders/Entity.vert", "Shaders/Entity.frag"),
      baseShader("Shaders/Basic.vert", "Shaders/Basic.frag")
{
    if(INSTANCE == nullptr) {
        INSTANCE = this;
    }
    else {
        throw std::runtime_error(std::string("Application already exists"));
    }

    window.setWindowPos(posX, posY);
    // 载入GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        throw std::runtime_error(std::string("Could initialize GLAD"));
    }
    // 获取版本信息
    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version  = glGetString(GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported " << version << std::endl;

#pragma region 设置全局属性
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS);    // depth-testing interprets a smaller value as "closer"

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    // glfwSwapInterval(GLFW_TRUE); // vsync
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 线框模式
    // glfwSetCursorPosCallback(window.GetHandle(), (GLFWcursorposfun) MouseCallback);
    // pGUI = std::make_unique<EmbeddedUI>(window.GetHandle());
    // pGUI->Init();
    glCheckError(__FILE__, __LINE__);
#pragma endregion


#pragma region 创建实体
    //    pCamera = std::make_unique<Camera>(glm::vec3(0.0f, 10.0f, 10.0f), -15.0f, -90.0f);
    //
    //    pLightDirectional = std::make_shared<LightDirectional>(
    //        glm::vec3(0.0f, 12.0f, 5.0f),
    //        glm::vec3(glm::radians(90.0f), 0.0f, glm::radians(45.0f)),
    //        glm::vec3(0.9f, 0.9f, 1.0f));
    //    pLightPoint = std::make_shared<LightPoint>(glm::vec3(1.0f, 8.0f, 3.0f));
    //
    //    models.emplace_back(std::make_shared<Model>(
    //        "D:/SourceCode/CppCode/Dxr3DEngine/Assets/test/utah-teapot.obj"));
    //    models[0]->SetPosition(glm::vec3(0.0f, 2.3f, -2.0f));
    //    models.emplace_back(std::make_shared<Model>(
    //        "D:/SourceCode/CppCode/Dxr3DEngine/Assets/nanosuit/nanosuit.obj"));
    //    //
    //    models.emplace_back(std::make_shared<Model>("D:/SourceCode/CppCode/OpenGL/Assets/test/test.obj"));

#pragma endregion

#pragma region 设置 uniform
    //   entityShader.use();
    //    entityShader.SetUniform("dirLight.direction", pLightDirectional->Direction);
    //    entityShader.SetUniform("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    //    entityShader.SetUniform("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    //    entityShader.SetUniform("dirLight.specular", 0.5f, 0.5f, 0.5f);
    //
    //    entityShader.SetUniform("pointLight.position", pLightPoint->Position);
    //    entityShader.SetUniform("pointLight.ambient", 0.05f, 0.05f, 0.05f);
    //    entityShader.SetUniform("pointLight.diffuse", 0.8f, 0.8f, 0.8f);
    //    entityShader.SetUniform("pointLight.specular", 1.0f, 1.0f, 1.0f);
    //    entityShader.SetUniform("pointLight.constant", pLightPoint->Constant);
    //    entityShader.SetUniform("pointLight.linear", pLightPoint->Linear);
    //    entityShader.SetUniform("pointLight.quadratic", pLightPoint->Quadratic);

#pragma endregion
}


void Application::run()
{
    // Make the window's context current
    glfwMakeContextCurrent(window.getHandle());

    while(!glfwWindowShouldClose(window.getHandle())) {

        Timer::preUpdate();

//        while(Timer::Accumulator() >= Timer::FixedDeltaTime()) {
//            Timer::FixedUpdate();
//            ECS_Engine->FixedUpdate(Timer::FixedDeltaTime().count());
//
//            /*cubeTransform.Rotate(1.0f, 1.0f, 1.0f);
//            cube2Transform.Rotate(1.0f, 0.0f, 0.0f);
//            cube3Transform.Rotate(0.5f, 0.5f, 0.0f);
//            cube4Transform.Rotate(0.0f, 0.5f, 2.0f);*/
//        }
//        ECS_Engine->Update(Timer::DeltaTime().count());

        // detech window related changes
        window.detectWindowDimensionChange();

        // execute the frame code
        update();

        // Swap Front and Back buffers (double buffering)
       // glfwSwapBuffers(window.GetHandle());

        // Pool and process events
        glfwPollEvents();
    }

    glfwTerminate();
}


void Application::update()
{
    //    ProcessInput();
    //    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //
    // #pragma region 渲染场景
    //    entityShader.Use();
    //    entityShader.SetUniform("cameraPos", pCamera->Position);
    //    entityShader.SetUniform("viewMat", pCamera->GetViewMat());
    //    entityShader.SetUniform("projMat", pCamera->GetProjectionMat());
    ////    Transform transform;
    ////    transform.Position.y = 8.0f;
    ////    transform.Position.x = 3.0f * sin(glfwGetTime());
    ////    transform.Position.z = 3.0f * cos(glfwGetTime());
    ////    pLightPoint->SetTransform(transform);
    ////    entityShader.SetUniform("pointLight.position", transform.Position);
    ////
    ////    RenderModels();
    //
    //    entityShader.Unuse();
    // #pragma endregion
    //
    //    // 渲染实体
    //    RenderBasic({pLightPoint, pLightDirectional});
}

//
// bool firstMouse = true;
// double lastX    = 0.0f;
// double lastY    = 0.0f;
// void Application::MouseCallback(GLFWwindow *window, double xpos, double ypos)
//{
//    if(Application::INSTANCE == nullptr) return;
//    if(firstMouse) {
//        lastX      = xpos;
//        lastY      = ypos;
//        firstMouse = false;
//    }
//    auto dx = static_cast<float>(xpos - lastX);
//    auto dy = static_cast<float>(lastY - ypos);
//    Application::INSTANCE->pCamera->ProcessMouseMovement(dx, dy, 0.05);
//    lastX = xpos;
//    lastY = ypos;
//}
//
// void Application::RenderBasic(const std::vector<std::shared_ptr<Entity>> &entities)
//{
//    baseShader.Use();
//    for(auto &entity : entities) {
//        baseShader.SetUniform("viewMat", pCamera->GetViewMat());
//        baseShader.SetUniform("projMat", pCamera->GetProjectionMat());
//        baseShader.SetUniform("modelMat", entity->GetModelMat());
//        baseShader.SetUniform("objRawColor", vec3(0.5f, 1.0f, 0.0f));
//        entity->Render(baseShader);
//    }
//    baseShader.Unuse();
//}
// void Application::RenderModels()
//{
//    for(auto model : models) {
//        glm::mat4 modelMat(1.0f);
//        modelMat = glm::translate(modelMat, model->GetPosition());
//        entityShader.SetUniform("modelMat", modelMat);
//        model->Render(entityShader);
//    }
//}
// void Application::RenderSkybox()
//{
////        skyboxShader.Use();
////        skyboxShader.SetUniform("viewMat",
////        glm::mat4(glm::mat3(pCamera->GetViewMat())));
////        skyboxShader.SetUniform("projMat", pCamera->GetProjectionMat());
////        skyboxShader.SetUniform("skybox", 0);
////        skybox->Render(skyboxShader);
////        skyboxShader.Unuse();
//}
// void Application::ProcessInput()
//{
//    if(pCamera == nullptr) return;
//    if(glfwGetKey(window.GetHandle(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window.GetHandle(), true);
//    float cameraSpeed = 2.5f * GetFrameDeltaTime();
//    if(glfwGetKey(window.GetHandle(), GLFW_KEY_LEFT_SHIFT)) cameraSpeed *= 8.0f;
//    if(glfwGetKey(window.GetHandle(), GLFW_KEY_E))
//        pCamera->Update(glm::vec3(0.0f, cameraSpeed, 0.0f));
//    if(glfwGetKey(window.GetHandle(), GLFW_KEY_SPACE))
//        pCamera->Update(glm::vec3(0.0f, cameraSpeed, 0.0f));
//    if(glfwGetKey(window.GetHandle(), GLFW_KEY_LEFT_CONTROL))
//        pCamera->Update(glm::vec3(0.0f, -cameraSpeed, 0.0f));
//    if(glfwGetKey(window.GetHandle(), GLFW_KEY_Q))
//        pCamera->Update(glm::vec3(0.0f, -cameraSpeed, 0.0f));
//    if(glfwGetKey(window.GetHandle(), GLFW_KEY_W))
//        pCamera->Update(cameraSpeed * pCamera->Forward);
//    if(glfwGetKey(window.GetHandle(), GLFW_KEY_S))
//        pCamera->Update(-cameraSpeed * pCamera->Forward);
//    if(glfwGetKey(window.GetHandle(), GLFW_KEY_A))
//        pCamera->Update(
//            -glm::normalize(glm::cross(pCamera->Forward, vec3(.0, 1., .0))) *
//            cameraSpeed);
//    if(glfwGetKey(window.GetHandle(), GLFW_KEY_D))
//        pCamera->Update(
//            glm::normalize(glm::cross(pCamera->Forward, vec3(.0, 1., .0))) *
//            cameraSpeed);
//}

} // namespace dxr::gl
