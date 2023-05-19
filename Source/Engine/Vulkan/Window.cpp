#include "Window.h"

#include <vulkan/vulkan_core.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace dxr {
Window::Window(int w, int h, std::string name) : width{ w }, height{ h }, windowName{ name } {
    initWindow();
}

void Window::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
}
void Window::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface){
    if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface");
    }

}
Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}
}  // namespace dxr
