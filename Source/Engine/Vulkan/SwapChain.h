#pragma once

#include "Device.h"

// vulkan headers
#include <vulkan/vulkan.h>

// std lib headers
#include <memory>
#include <string>
#include <vector>

namespace Dxr
{

class SwapChain
{
public:
    static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

    SwapChain(Device &deviceRef, VkExtent2D extent);
    SwapChain(
        Device &deviceRef, VkExtent2D extent, std::shared_ptr<SwapChain> previous);
    ~SwapChain();

    SwapChain(const SwapChain &)      = delete;
    void operator=(const SwapChain &) = delete;

    VkFramebuffer GetFrameBuffer(int index) { return swapChainFrameBuffers[index]; }
    VkRenderPass GetRenderPass() { return renderPass; }
    VkImageView GetImageView(int index) { return swapChainImageViews[index]; }
    // 2或者3，取决于支持双重缓冲还是三重缓冲
    size_t GetImageCount() { return swapChainImages.size(); }
    VkFormat GetSwapChainImageFormat() { return swapChainImageFormat; }
    VkExtent2D GetSwapChainExtent() { return swapChainExtent; }
    uint32_t GetWidth() { return swapChainExtent.width; }
    uint32_t GetHeight() { return swapChainExtent.height; }
    float GetExtentAspectRatio()
    {
        return static_cast<float>(swapChainExtent.width) /
            static_cast<float>(swapChainExtent.height);
    }
    VkFormat FindDepthFormat();

    VkResult AcquireNextImage(uint32_t *imageIndex);
    VkResult SubmitCommandBuffers(const VkCommandBuffer *buffers, uint32_t *imageIndex);

private:
    void Init();
    void CreateSwapChain();
    void CreateImageViews();
    void CreateDepthResources();
    void CreateRenderPass();
    void CreateFrameBuffers();
    void CreateSyncObjects();

    // Helper functions
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(
        const std::vector<VkSurfaceFormatKHR> &availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(
        const std::vector<VkPresentModeKHR> &availablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;

    std::vector<VkFramebuffer> swapChainFrameBuffers;
    VkRenderPass renderPass;

    std::vector<VkImage> depthImages;
    std::vector<VkDeviceMemory> depthImageMemories;
    std::vector<VkImageView> depthImageViews;
    std::vector<VkImage> swapChainImages;
    std::vector<VkImageView> swapChainImageViews;

    Device &device;
    VkExtent2D windowExtent;
    VkSwapchainKHR swapChain;
    std::shared_ptr<SwapChain> oldSwapChain;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;
    size_t currentFrame = 0;
};

} // namespace Dxr
