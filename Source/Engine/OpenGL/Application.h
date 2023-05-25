#pragma once

#include <memory>
#include <string>
#include <vector>

//#include "../Components/Camera.h"
//#include "Common/Light/LightDirectional.h"
//#include "Common/Light/LightPoint.h"
#include "Shader.h"
#include "Window.h"

namespace dxr::gl
{
struct GLFWwindow;
class Application
{
public:
    Application(
        int width  = 800,
        int height = 600,
        int posX   = 0,
        int posY   = 0,

        const std::string &title = "Application");
    ~Application()                               = default;
    Application(const Application &)             = delete;
    Application &operator=(const Application &)  = delete;
    Application(Application &&)                  = delete;
    Application &operator=(const Application &&) = delete;
    static Application *INSTANCE;

    // application Run
    void run();

    Window window;
    void update();

//    std::unique_ptr<Camera> pCamera;
//    std::unique_ptr<IGUI> pGUI;
//
//    std::shared_ptr<LightDirectional> pLightDirectional;
//    std::shared_ptr<LightPoint> pLightPoint;
//    std::vector<std::shared_ptr<Entity>> models;

protected:
//    void RenderSkybox();
//    void RenderBasic(const std::vector<std::shared_ptr<Entity>> &entities);
//    void RenderModels();
//    void ProcessInput();
private:
    static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
    ShaderProgram entityShader;
    ShaderProgram baseShader;
};
} // namespace Dxr::gl

