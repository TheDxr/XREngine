#include "Application.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <array>
#include <memory>
#include <stdexcept>
#include <stdint.h>
#include "Pipeline.h"

namespace Dxr
{

struct SimplePushConstantData
{
    glm::vec2 offset;
    //glm::vec3 color;
};
Application::Application(int width, int height, int posX, int posY, std::string title)
    : window(width, height, "Hello Vulkan!")
{
    // auto console = spdlog::stdout_color_mt("console");
    LoadModels();
    CreatePipelineLayout();
    RecreateSwapChain();
    CreateCommandBuffers();
}
void Application::CreateCommandBuffers()
{
    commandBuffers.resize(swapChain->GetImageCount());

    VkCommandBufferAllocateInfo allocateInfo{};
    allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    // PRIMARY能直接提交但不能被其他调用
    allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY; // （PRIMARY 或者 SECONDARY）
    allocateInfo.commandPool        = device_.GetCommandPool();
    allocateInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

    if(vkAllocateCommandBuffers(
           device_.GetDevice(), &allocateInfo, commandBuffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("分配Command Buffers 失败!");
    }
}

void Application::CreatePipelineLayout()
{
    VkPushConstantRange pushConstantRange{};
    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    pushConstantRange.offset     = 0;
    pushConstantRange.size       = sizeof(SimplePushConstantData);

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType          = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pSetLayouts    = nullptr;
    pipelineLayoutInfo.pushConstantRangeCount = 1;
    pipelineLayoutInfo.pPushConstantRanges    = &pushConstantRange;
    if(vkCreatePipelineLayout(
           device_.GetDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout) !=
       VK_SUCCESS) {
        throw std::runtime_error("创建pipeline layout失败!");
    }
}

void Application::CreatePipeline()
{
    PipelineConfigInfo configInfo{};
    Pipeline::DefaultPipelineConfigInfo(configInfo);

    configInfo.renderPass     = swapChain->GetRenderPass();
    configInfo.pipelineLayout = pipelineLayout;
    pipeline                  = std::make_unique<Pipeline>(
        device_, "Shaders/vulkan.vert.spv", "Shaders/vulkan.frag.spv", configInfo);
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
    auto result = swapChain->AcquireNextImage(&imageIndex);
    if(result == VK_ERROR_OUT_OF_DATE_KHR) {
        RecreateSwapChain();
        return;
    }
    if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("Failed to acquire swap chain image!");
    }

    RecordCommandBuffer(imageIndex);
    result = swapChain->SubmitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
    if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR ||
       window.Resized()) {
        window.ResetWindowResizedFlag();
        RecreateSwapChain();
        return;
    }
    if(result != VK_SUCCESS) {
        throw std::runtime_error("Failed to present swap chain image!");
    }
}
void Application::LoadModels()
{
    std::vector<Mesh::Vertex> vertices{
        {{0.0f, -0.5f}}, {{0.5f, 0.5f}}, {{-0.5f, 0.5f}}};

    mesh = std::make_unique<Mesh>(device_, vertices);
}
void Application::RecreateSwapChain()
{
    auto extent = window.GetExtent();
    while(extent.width == 0 || extent.height == 0) {
        extent = window.GetExtent();
        glfwWaitEvents();
    }
    vkDeviceWaitIdle(device_.GetDevice());

    if(swapChain == nullptr) {
        swapChain = std::make_unique<SwapChain>(device_, extent);
    }
    else {
        swapChain = std::make_unique<SwapChain>(device_, extent, std::move(swapChain));
        if(swapChain->GetImageCount() != commandBuffers.size()) {
            FreeCommandBuffers();
            CreateCommandBuffers();
        }
    }
    CreatePipeline();
}
void Application::RecordCommandBuffer(int imageIndex)
{
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if(vkBeginCommandBuffer(commandBuffers[imageIndex], &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("记录Command Buffer失败!");
    }

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType       = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass  = swapChain->GetRenderPass();
    renderPassInfo.framebuffer = swapChain->GetFrameBuffer(imageIndex);

    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = swapChain->GetSwapChainExtent();

    std::array<VkClearValue, 2> clearValues{};       // 清除颜色和深度缓冲区
    clearValues[0].color = {0.1f, 0.1f, 0.2f, 1.0f}; // 底色
    clearValues[1].depthStencil = {1.0f, 0}; // 深度值缓冲区1代表最远，0代表最近
    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues    = clearValues.data();

    vkCmdBeginRenderPass(
        commandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    VkViewport viewport{};
    viewport.x        = 0.0f;
    viewport.y        = 0.0f;
    viewport.width    = static_cast<float>(swapChain->GetSwapChainExtent().width);
    viewport.height   = static_cast<float>(swapChain->GetSwapChainExtent().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    VkRect2D scissor{{0, 0}, swapChain->GetSwapChainExtent()};
    vkCmdSetViewport(commandBuffers[imageIndex], 0, 1, &viewport);
    vkCmdSetScissor(commandBuffers[imageIndex], 0, 1, &scissor);


    pipeline->Bind(commandBuffers[imageIndex]);
    mesh->Bind(commandBuffers[imageIndex]);

    for(int j = 0 ;j < 4;j++) {
        SimplePushConstantData push{};
        push.offset = {0.5f * j, 0.5f * j};

        vkCmdPushConstants(
            commandBuffers[imageIndex],
            pipelineLayout,
            VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
            0,
            sizeof(SimplePushConstantData),
            &push);
        mesh->Draw(commandBuffers[imageIndex]);
    }

    vkCmdEndRenderPass(commandBuffers[imageIndex]);
    if(vkEndCommandBuffer(commandBuffers[imageIndex]) != VK_SUCCESS) {
        throw std::runtime_error("无法记录command Buffers");
    }
}
void Application::FreeCommandBuffers()
{
    vkFreeCommandBuffers(
        device_.GetDevice(),
        device_.GetCommandPool(),
        static_cast<uint32_t>(commandBuffers.size()),
        commandBuffers.data());
    commandBuffers.clear();
}

} // namespace Dxr
