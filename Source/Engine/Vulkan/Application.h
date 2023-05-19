#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Device.h"
#include "Pipeline.h"
#include "SwapChain.h"
#include "Window.h"

#include <spdlog/spdlog.h>

namespace Dxr
{
class Application
{
public:
    Application() = default;
    Application(int width, int height, int posX = 0, int posY = 0, std::string title = "Application")
    {
        // auto console = spdlog::stdout_color_mt("console");
        CreatePipelineLayout();
        CreatePipeline();
        CreateCommandBuffers();
    }

    virtual ~Application()                      = default;
    Application(const Application &)            = delete;
    Application &operator=(const Application &) = delete;

    // window control
    void Exit() {}
    // delta mTime between frame and mTime from beginning
    //    float GetFrameDeltaTime();
    //    float GetTime() const;
    // application Run
    void Run();
    // Application information
    //    int GetWidth();
    //    int GetHeight();
    //    float GetWindowRatio();
    //    bool WindowDimensionChanged();

protected:
    // TODO: window
    Window window{800, 600, "Hello Vulkan!"};
    virtual void Update() {  uint32_t imageIndex;
        auto result = dxrSwapChain.AcquireNextImage(&imageIndex);
    }
    // Time:
    //    float mTime = 0.0f;
    //    float mDeltaTime = 0.0f;

private:
    std::shared_ptr<spdlog::logger> logger = spdlog::get("console");
    void CreateCommandBuffers();
    void CreatePipelineLayout();
    void CreatePipeline();

    Device device_{window};
    SwapChain dxrSwapChain{device_, window.GetExtent()};
    VkPipelineLayout pipelineLayout;
    std::unique_ptr<Pipeline> dxrPipeline;
    std::vector<VkCommandBuffer> commandBuffers;
};
} // namespace Dxr
