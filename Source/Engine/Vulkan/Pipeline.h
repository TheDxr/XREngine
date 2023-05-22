#pragma once

#include <iostream>

#include "Device.h"

#include <stdint.h>
#include <string>
#include <vector>
#include <vulkan/vulkan_core.h>

namespace Dxr
{

struct PipelineConfigInfo
{
    PipelineConfigInfo()                                      = default;
    ~PipelineConfigInfo()                                     = default;
    PipelineConfigInfo(const PipelineConfigInfo &)            = delete;
    PipelineConfigInfo &operator=(const PipelineConfigInfo &) = delete;

    VkPipelineViewportStateCreateInfo viewportInfo{};
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo{}; // 输入组装
    VkPipelineRasterizationStateCreateInfo rasterizationInfo{}; // 光栅化
    VkPipelineMultisampleStateCreateInfo multisampleInfo{};     // 多重采样
    VkPipelineColorBlendAttachmentState colorBlendAttachment{}; // 颜色混合附件
    VkPipelineColorBlendStateCreateInfo colorBlendInfo{};       // 颜色混合
    VkPipelineDepthStencilStateCreateInfo depthStencilInfo{};   // 深度测试
    std::vector<VkDynamicState> dynamicStateEnables;
    VkPipelineDynamicStateCreateInfo dynamicStateInfo{};
    VkPipelineLayout pipelineLayout = nullptr;
    VkRenderPass renderPass         = nullptr;
    uint32_t subpass                = 0;
};

class Pipeline
{
public:
    Pipeline(Device &device, const std::string &vertFilePath, const std::string &fragFilePath,
             PipelineConfigInfo &configInfo);
    ~Pipeline();
    Pipeline(const Pipeline &)        = delete;
    void operator=(const Pipeline &)  = delete;
    Pipeline(const Pipeline &&)       = delete;
    void operator=(const Pipeline &&) = delete;
    void Bind(VkCommandBuffer commandBuffer);
    static void DefaultPipelineConfigInfo(PipelineConfigInfo &configInfo);

private:
    static std::vector<char> ReadFile(const std::string &filepath);
    void CreateGraphicsPipeline(const std::string &vertFilePath, const std::string &fragFilePath,
                                PipelineConfigInfo &configInfo);

    void CreateShaderModule(const std::vector<char> &code, VkShaderModule *shaderModule);

    // TODO : unsafe
    Device &device_;
    VkPipeline graphicsPipeline;
    VkShaderModule vertShaderModule;
    VkShaderModule fragShaderModule;
};

} // namespace Dxr
