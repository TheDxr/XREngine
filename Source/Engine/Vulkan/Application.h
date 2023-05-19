//#pragma once
//
//#include "dxr_device.hpp"
//#include "dxr_pipeline.hpp"
//#include "dxr_swap_chain.hpp"
//#include "dxr_window.hpp"
//#include "vulkan/vulkan_core.h"
//
//#include <memory>
//#include <vector>
//
//namespace dxr {
//class FirstApp {
//  public:
//    static constexpr int WIDTH = 800;
//    static constexpr int HEIGHT = 600;
//
//    FirstApp();
//    ~FirstApp();
//    FirstApp(const FirstApp&) = delete;
//    FirstApp& operator=(const FirstApp&) = delete;
//
//    void run();
//
//  private:
//    void createPipeline();
//    void createPipelineLayout();
//    void createCommandBuffers();
//    void drawFrame();
//
//    Window dxrWindow{ WIDTH, HEIGHT, "Hello Vulkan!" };
//    Device dxrDevice{ dxrWindow };
//    SwapChain dxrSwapChain{ dxrDevice, dxrWindow.getExtent() };
//
//    VkPipelineLayout pipelineLayout;
//
//    std::unique_ptr<Pipeline> dxrPipeline;
//    std::vector<VkCommandBuffer> commandBuffers;
//};
//}  // namespace dxr
