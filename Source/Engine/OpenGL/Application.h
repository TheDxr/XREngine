#pragma once

#include <memory>
#include <string>
#include <vector>
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

    void run();
    Window window;
    void update();
    static int getOne(){return 1;}
protected:
//    void RenderSkybox();
//    void RenderBasic(const std::vector<std::shared_ptr<Entity>> &entities);
//    void RenderModels();
private:
    void processInput();
    std::unique_ptr<ShaderProgram> entityShader;
    std::unique_ptr<ShaderProgram> baseShader;
};
} // namespace Dxr::gl

