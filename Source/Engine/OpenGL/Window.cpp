#include "Window.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include <stdexcept>
namespace dxr::gl
{
Window::Window(int width, int height, const std::string &title) : width(width), height(height)
{
    if(!glfwInit()) {
        throw std::runtime_error("Couldn't init GLFW");
    }
    // setting the opengl version
    int major = 3;
    int minor = 2;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if(!window_) {
        glfwTerminate();
        throw std::runtime_error("Couldn't create a window");
    }
    //glfwSetWindowPos(window_, 400, 240);
    glfwMakeContextCurrent(window_);
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
    spdlog::info("GLFW window initialized");
}
void Window::detectWindowDimensionChange()
{
    int w, h;
    glfwGetWindowSize(window_, &w, &h);
    if(w != width || h != height) {
        dimensionChanged = true;
        width            = w;
        height           = h;
    }
    else {
        dimensionChanged = false;
    }
}
float Window::getWindowRatio()
{
    glfwGetWindowSize(window_, &width, &height);
    return (float)width / (float)height;
}
int Window::getHeight()
{
    glfwGetWindowSize(window_, &width, &height);
    return height;
}
int Window::getWidth()
{
    glfwGetWindowSize(window_, &width, &height);
    return width;
}
bool Window::windowDimensionChanged() { return dimensionChanged; }
void Window::setWindowPos(int x, int y) { glfwSetWindowPos(window_, x, y); }

} // namespace dxr::gl