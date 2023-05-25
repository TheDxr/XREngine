#include "Window.h"

#include <spdlog/spdlog.h>
#include <stdexcept>
namespace dxr::gl
{
Window::Window(int width, int height, const std::string &title) : width(width), height(height)
{
    if(!glfwInit()) {
        throw std::runtime_error("Couldn't init GLFW");
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // setting the opengl version
    int major = 3;
    int minor = 2;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if(!window) {
        glfwTerminate();
        throw std::runtime_error("Couldn't create a window");
    }
    spdlog::info("GLFW window initialized");
}
void Window::detectWindowDimensionChange()
{
    int w, h;
    glfwGetWindowSize(window, &w, &h);
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
    glfwGetWindowSize(window, &width, &height);
    return (float)width / (float)height;
}
int Window::getHeight()
{
    glfwGetWindowSize(window, &width, &height);
    return height;
}
int Window::getWidth()
{
    glfwGetWindowSize(window, &width, &height);
    return width;
}
bool Window::windowDimensionChanged() { return dimensionChanged; }
void Window::setWindowPos(int x, int y) { glfwSetWindowPos(window, x, y); }

} // namespace dxr::gl