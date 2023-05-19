#include "Window.h"

#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vulkan/vulkan_core.h>

namespace Dxr
{
Window::Window(int w, int h, std::string name) : width{w}, height{h}, windowName{name} { Init(); }

void Window::Init()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    //glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
}
void Window::CreateWindowSurface(VkInstance instance, VkSurfaceKHR *surface)
{
    if(glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window GetSurface");
    }
}
Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
} // namespace Dxr
