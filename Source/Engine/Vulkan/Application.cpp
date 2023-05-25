#include "Application.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <array>
#include <memory>
#include <stdexcept>
#include <stdint.h>
#include "Pipeline.h"

namespace dxr
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
    loadModels();
    createPipelineLayout();
    recreateSwapChain();
    createCommandBuffers();
}
void Application::createCommandBuffers()
{
    commandBuffers_.resize(swapChain_->getImageCount());

    VkCommandBufferAllocateInfo allocateInfo{};
    allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    // PRIMARY能直接提交但不能被其他调用
    allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY; // （PRIMARY 或者 SECONDARY）
    allocateInfo.commandPool        = device_.getCommandPool();
    allocateInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers_.size());

    if(vkAllocateCommandBuffers(
           device_.getDevice(), &allocateInfo, commandBuffers_.data()) != VK_SUCCESS) {
        throw std::runtime_error("分配Command Buffers 失败!");
    }
}

void Application::createPipelineLayout()
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
           device_.getDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout_) !=
       VK_SUCCESS) {
        throw std::runtime_error("创建pipeline layout失败!");
    }
}

void Application::createPipeline()
{
    PipelineConfigInfo configInfo{};
    Pipeline::defaultPipelineConfigInfo(configInfo);

    configInfo.renderPass     = swapChain_->getRenderPass();
    configInfo.pipelineLayout = pipelineLayout_;
    pipeline_                 = std::make_unique<Pipeline>(
        device_, "Shaders/vulkan.vert.spv", "Shaders/vulkan.frag.spv", configInfo);
}

void Application::run()
{
    while(!window.shouldClose()) {
        glfwPollEvents();
        update();
    }
}
void Application::update()
{
    uint32_t imageIndex;
    auto result = swapChain_->acquireNextImage(&imageIndex);
    if(result == VK_ERROR_OUT_OF_DATE_KHR) {
        recreateSwapChain();
        return;
    }
    if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("Failed to acquire swap chain image!");
    }

    recordCommandBuffer(imageIndex);
    result = swapChain_->submitCommandBuffers(&commandBuffers_[imageIndex], &imageIndex);
    if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR ||
       window.resized()) {
        window.resetWindowResizedFlag();
        recreateSwapChain();
        return;
    }
    if(result != VK_SUCCESS) {
        throw std::runtime_error("Failed to present swap chain image!");
    }
}
void Application::loadModels()
{
    std::vector<Mesh::Vertex> vertices{
        {{0.0f, -0.5f}}, {{0.5f, 0.5f}}, {{-0.5f, 0.5f}}};

    mesh = std::make_unique<Mesh>(device_, vertices);
}
void Application::recreateSwapChain()
{
    auto extent = window.getExtent();
    while(extent.width == 0 || extent.height == 0) {
        extent = window.getExtent();
        glfwWaitEvents();
    }
    vkDeviceWaitIdle(device_.getDevice());

    if(swapChain_ == nullptr) {
        swapChain_ = std::make_unique<SwapChain>(device_, extent);
    }
    else {
        swapChain_ = std::make_unique<SwapChain>(device_, extent, std::move(swapChain_));
        if(swapChain_->getImageCount() != commandBuffers_.size()) {
            freeCommandBuffers();
            createCommandBuffers();
        }
    }
    createPipeline();
}
void Application::recordCommandBuffer(int imageIndex)
{
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if(vkBeginCommandBuffer(commandBuffers_[imageIndex], &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("记录Command Buffer失败!");
    }

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType       = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass  = swapChain_->getRenderPass();
    renderPassInfo.framebuffer = swapChain_->getFrameBuffer(imageIndex);

    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = swapChain_->getSwapChainExtent();

    std::array<VkClearValue, 2> clearValues{};       // 清除颜色和深度缓冲区
    clearValues[0].color = {0.1f, 0.1f, 0.2f, 1.0f}; // 底色
    clearValues[1].depthStencil = {1.0f, 0}; // 深度值缓冲区1代表最远，0代表最近
    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues    = clearValues.data();

    vkCmdBeginRenderPass(commandBuffers_[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    VkViewport viewport{};
    viewport.x        = 0.0f;
    viewport.y        = 0.0f;
    viewport.width    = static_cast<float>(swapChain_->getSwapChainExtent().width);
    viewport.height   = static_cast<float>(swapChain_->getSwapChainExtent().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    VkRect2D scissor{{0, 0}, swapChain_->getSwapChainExtent()};
    vkCmdSetViewport(commandBuffers_[imageIndex], 0, 1, &viewport);
    vkCmdSetScissor(commandBuffers_[imageIndex], 0, 1, &scissor);


    pipeline_->bind(commandBuffers_[imageIndex]);
    mesh->bind(commandBuffers_[imageIndex]);

    for(int j = 0 ;j < 4;j++) {
        SimplePushConstantData push{};
        push.offset = {0.5f * j, 0.5f * j};

        vkCmdPushConstants(
            commandBuffers_[imageIndex],
            pipelineLayout_,
            VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
            0,
            sizeof(SimplePushConstantData),
            &push);
        mesh->draw(commandBuffers_[imageIndex]);
    }

    vkCmdEndRenderPass(commandBuffers_[imageIndex]);
    if(vkEndCommandBuffer(commandBuffers_[imageIndex]) != VK_SUCCESS) {
        throw std::runtime_error("无法记录command Buffers");
    }
}
void Application::freeCommandBuffers()
{
    vkFreeCommandBuffers(
        device_.getDevice(),
        device_.getCommandPool(),
        static_cast<uint32_t>(commandBuffers_.size()),
        commandBuffers_.data());
    commandBuffers_.clear();
}

} // namespace Dxr
