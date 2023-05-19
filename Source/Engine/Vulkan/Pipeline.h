#pragma once

#include "Device.h"

#include <stdint.h>
#include <string>
#include <vector>
#include <vulkan/vulkan_core.h>

namespace dxr
{

struct PipelineConfigInfo
{
    VkViewport viewport;
    VkRect2D scissor;
    // VkPipelineViewportStateCreateInfo viewportInfo;
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
    VkPipelineRasterizationStateCreateInfo rasterizationInfo;
    VkPipelineMultisampleStateCreateInfo multisampleInfo;
    VkPipelineColorBlendAttachmentState colorBlendAttachment;
    VkPipelineColorBlendStateCreateInfo colorBlendInfo;
    VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
    // std::vector<VkDynamicState> dynamicStateEnables;
    // VkPipelineDynamicStateCreateInfo dynamicStateInfo;
    VkPipelineLayout pipelineLayout = nullptr;
    VkRenderPass renderPass         = nullptr;
    uint32_t subpass                = 0;
};
class Pipeline
{
public:
    Pipeline(Device &device, const std::string &vertFilePath, const std::string &fragFilePath,
             const PipelineConfigInfo &configInfo);
    ~Pipeline();
    Pipeline(const Pipeline &)       = delete;
    void operator=(const Pipeline &) = delete;

    void bind(VkCommandBuffer commandBuffer);
    static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

private:
    static std::vector<char> readFile(const std::string &filepath);
    void createGraphicsPipeline(const std::string &vertFilePath, const std::string &fragFilePath,
                                const PipelineConfigInfo &configInfo);

    void createShaderModule(const std::vector<char> &code, VkShaderModule *shaderModule);

    Device &dxrDevice;
    VkPipeline graphicsPipeline;
    VkShaderModule vertShaderModule;
    VkShaderModule fragShaderModule;
};

} // namespace dxr
