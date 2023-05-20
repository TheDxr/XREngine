#include "Application.h"

#include "Pipeline.h"
#include <array>
#include <memory>
#include <stdexcept>
#include <stdint.h>

namespace Dxr
{

void Application::CreateCommandBuffers()
{
    commandBuffers.resize(swapChain.GetImageCount());

    VkCommandBufferAllocateInfo allocateInfo{};
    allocateInfo.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    // PRIMARY能直接提交但不能被其他调用
    allocateInfo.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;//（PRIMARY 或者 SECONDARY）
    allocateInfo.commandPool        = device_.GetCommandPool();
    allocateInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

    if(vkAllocateCommandBuffers(device_.GetDevice(), &allocateInfo, commandBuffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("分配Command Buffers 失败!");
    }
    for(int i = 0; i < commandBuffers.size(); i++) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if(vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("记录Command Buffer失败!");
        }

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType       = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass  = swapChain.GetRenderPass();
        renderPassInfo.framebuffer = swapChain.GetFrameBuffer(i);

        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = swapChain.GetSwapChainExtent();

        std::array<VkClearValue, 2> clearValues{};// 清除颜色和深度缓冲区
        clearValues[0].color           = {0.1f, 0.1f, 0.2f, 1.0f};// 底色
        clearValues[1].depthStencil    = {1.0f, 0}; // 深度值缓冲区1代表最远，0代表最近
        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues    = clearValues.data();

        vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        pipeline->Bind(commandBuffers[i]);
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
    auto configInfo = Pipeline::DefaultPipelineConfigInfo(swapChain.GetWidth(), swapChain.GetHeight());
    configInfo.renderPass     = swapChain.GetRenderPass();
    configInfo.pipelineLayout = pipelineLayout;
    pipeline = std::make_unique<Pipeline>(
        device_, "D:/SourceCode/CppCode/Vulkan/shader/simple_shader.vert.spv",
        "D:/SourceCode/CppCode/Vulkan/shader/simple_shader.frag.spv", configInfo);
}

void Application::Run()
{
    while(!window.ShouldClose()) {
        glfwPollEvents();
        Update();
    }
}
void Application::Update()
{
    uint32_t imageIndex;
    auto result = swapChain.AcquireNextImage(&imageIndex);
    if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
    {
        throw std::runtime_error("Failed to acquire swap chain image!");
    }
    result = swapChain.SubmitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
    if(result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to present swap chain image!");
    }
}
} // namespace Dxr
