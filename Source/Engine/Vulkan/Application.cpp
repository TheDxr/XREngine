#include "Application.h"

#include <array>
#include <memory>
#include <stdexcept>
#include <stdint.h>

namespace Dxr
{

// FirstApp::FirstApp() {

//}
// FirstApp::~FirstApp() {
//    vkDestroyPipelineLayout(dxrDevice.GetDevice(), pipelineLayout, nullptr);
//}
// void FirstApp::run() {

//}

void Application::CreateCommandBuffers()
{
    commandBuffers.resize(dxrSwapChain.ImageCount());

    VkCommandBufferAllocateInfo allocateInfo{};
    allocateInfo.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocateInfo.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocateInfo.commandPool        = device_.GetCommandPool();
    allocateInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

    if(vkAllocateCommandBuffers(device_.GetDevice(), &allocateInfo, commandBuffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("分配Command Buffers 失败!");
    }
    for(int i = 0; i < commandBuffers.size(); i++) {
        VkCommandBufferBeginInfo beginInfo;
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if(vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("记录Command Buffer失败!");
        }

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType       = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass  = dxrSwapChain.GetRenderPass();
        renderPassInfo.framebuffer = dxrSwapChain.GetFrameBuffer(i);

        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = dxrSwapChain.GetSwapChainExtent();

        std::array<VkClearValue, 2> clearValues{};
        clearValues[0].color           = {0.1f, 0.1f, 0.1f, 1.0f};
        clearValues[1].depthStencil    = {1.0f, 0};
        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues    = clearValues.data();

        vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);


        dxrPipeline->Bind(commandBuffers[i]);
        vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

        vkCmdEndRenderPass(commandBuffers[i]);
        if(vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("无法记录command Buffers");
        }
    }
}
void Application::CreatePipelineLayout()
{
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount         = 0;
    pipelineLayoutInfo.pSetLayouts            = nullptr;
    pipelineLayoutInfo.pushConstantRangeCount = 0;
    pipelineLayoutInfo.pPushConstantRanges    = nullptr;
    if(vkCreatePipelineLayout(device_.GetDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
        throw std::runtime_error("创建pipeline layout失败!");
    }
}
void Application::CreatePipeline()
{
    auto pipelineConfig           = Pipeline::DefaultPipelineConfigInfo(dxrSwapChain.Width(), dxrSwapChain.Height());
    pipelineConfig.renderPass     = dxrSwapChain.GetRenderPass();
    pipelineConfig.pipelineLayout = pipelineLayout;
    dxrPipeline =
        std::make_unique<Pipeline>(device_, "D:/SourceCode/CppCode/Vulkan/shader/simple_shader.vert.spv",
                                   "D:/SourceCode/CppCode/Vulkan/shader/simple_shader.frag.spv", pipelineConfig);
}

void Application::Run()
{
    while(!window.ShouldClose()) {
        // Update();
        glfwPollEvents();
    }
}
} // namespace Dxr