#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Device.h"
#include "Mesh.h"
#include "Pipeline.h"
#include "SwapChain.h"
#include "Window.h"


#include <spdlog/spdlog.h>

namespace dxr
{
class Application
{
public:
    Application(int width, int height, int posX = 0, int posY = 0, std::string title = "Application");

    virtual ~Application()                      = default;
    Application(const Application &)            = delete;
    Application &operator=(const Application &) = delete;

    // delta mTime between frame and mTime from beginning
    // float GetFrameDeltaTime();
    // float GetTime() const;
    void run();
    Window&getWindow() { return window; }
protected:
    Window window;
    virtual void update();
    // Time:
    //    float mTime = 0.0f;
    //    float mDeltaTime = 0.0f;
    std::unique_ptr<Mesh> mesh;
private:
    void createCommandBuffers();
    void createPipelineLayout();
    void createPipeline();
    void freeCommandBuffers();
    void loadModels();
    void recreateSwapChain();
    void recordCommandBuffer(int imageIndex);

    Device device_{window};
    std::unique_ptr<SwapChain> swapChain_;// {device_, window.GetExtent()};
    VkPipelineLayout pipelineLayout_;

    std::unique_ptr<Pipeline> pipeline_;
    std::vector<VkCommandBuffer> commandBuffers_;
};
} // namespace Dxr
