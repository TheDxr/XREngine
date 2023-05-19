//#include "first_app.hpp"
//#include "vulkan/vulkan_core.h"
////#include "vulkan/vulkan_core.h"
//#include <array>
//#include <memory>
//#include <stdexcept>
//#include <stdint.h>
//
//namespace dxr {
//
//FirstApp::FirstApp() {
//    createPipelineLayout();
//    createPipeline();
//    createCommandBuffers();
//}
//FirstApp::~FirstApp() {
//    vkDestroyPipelineLayout(dxrDevice.device(), pipelineLayout, nullptr);
//}
//void FirstApp::run() {
//    while (!dxrWindow.shouldClose()) {
//        glfwPollEvents();
//    }
//}
//
//void FirstApp::createPipeline() {
//    auto pipelineConfig =
//        Pipeline::defaultPipelineConfigInfo(dxrSwapChain.width(), dxrSwapChain.height());
//    pipelineConfig.renderPass = dxrSwapChain.getRenderPass();
//    pipelineConfig.pipelineLayout = pipelineLayout;
//    dxrPipeline =
//        std::make_unique<Pipeline>(dxrDevice,
//                                      "D:/SourceCode/CppCode/Vulkan/shader/simple_shader.vert.spv",
//                                      "D:/SourceCode/CppCode/Vulkan/shader/simple_shader.frag.spv",
//                                      pipelineConfig);
//}
//void FirstApp::createPipelineLayout() {
//    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
//    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
//    pipelineLayoutInfo.setLayoutCount = 0;
//    pipelineLayoutInfo.pSetLayouts = nullptr;
//    pipelineLayoutInfo.pushConstantRangeCount = 0;
//    pipelineLayoutInfo.pPushConstantRanges = nullptr;
//    if (vkCreatePipelineLayout(dxrDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout)
//        != VK_SUCCESS) {
//        throw std::runtime_error("创建pipeline layout失败!");
//    }
//}
//void FirstApp::createCommandBuffers() {
//    commandBuffers.resize(dxrSwapChain.imageCount());
//
//    VkCommandBufferAllocateInfo allocateInfo{};
//    allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
//    allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
//    allocateInfo.commandPool = dxrDevice.getCommandPool();
//    allocateInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());
//
//    if (vkAllocateCommandBuffers(dxrDevice.device(), &allocateInfo, commandBuffers.data())
//        != VK_SUCCESS) {
//        throw std::runtime_error("分配Command Buffers 失败!");
//    }
//    for (int i = 0; i < commandBuffers.size(); i++) {
//        VkCommandBufferBeginInfo beginInfo;
//        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
//
//        if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
//            throw std::runtime_error("记录Command Buffer失败!");
//        }
//
//        VkRenderPassBeginInfo renderPassInfo{};
//        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
//        renderPassInfo.renderPass = dxrSwapChain.getRenderPass();
//        renderPassInfo.framebuffer = dxrSwapChain.getFrameBuffer(i);
//
//        renderPassInfo.renderArea.offset = { 0, 0 };
//        renderPassInfo.renderArea.extent = dxrSwapChain.getSwapChainExtent();
//
//        std::array<VkClearValue, 2> clearValues{};
//        clearValues[0].color = {0.1f, 0.1f, 0.1f ,1.0f};
//        clearValues[1].depthStencil = {1.0f, 0};
//        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
//        renderPassInfo.pClearValues = clearValues.data();
//
//        vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
//
//
//        dxrPipeline->bind(commandBuffers[i]);
//        vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);
//
//        vkCmdEndRenderPass(commandBuffers[i]);
//        if(vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
//            throw std::runtime_error("无法记录command Buffers");
//        }
//    }
//}
//void FirstApp::drawFrame() {
//
//    uint32_t imageIndex;
//    auto result = dxrSwapChain.acquireNextImage(&imageIndex);
//
//
//}
//}  // namespace dxr