#pragma once

#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>
namespace Dxr
{
class Window
{
public:
    Window(int w, int h, std::string name);
    ~Window();

    Window(const Window &)            = delete;
    Window &operator=(const Window &) = delete;

    bool ShouldClose() { return glfwWindowShouldClose(window); }
    VkExtent2D GetExtent() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }
    void CreateWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

private:
    void Init();
    const int width;
    const int height;
    std::string windowName;
    GLFWwindow *window;
};
} // namespace Dxr