#include "Pipeline.h"
#include "Device.h"
#include "Mesh.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <vulkan/vulkan_core.h>

namespace Dxr
{

std::vector<char> Pipeline::ReadFile(const std::string &filepath)
{
    std::fstream file{
        filepath, std::ios::ate | std::ios::binary | std::ios::in};
    if(!file.is_open()) {
        throw std::runtime_error("failed to open file: " + filepath);
    }

    size_t fileSize = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();
    return buffer;
}

Pipeline::Pipeline(
    Device &device,
    const std::string &vertFilePath,
    const std::string &fragFilePath,
    PipelineConfigInfo &configInfo)
    : device_(device)
{
    CreateGraphicsPipeline(vertFilePath, fragFilePath, configInfo);
}

Pipeline::~Pipeline()
{
    vkDestroyShaderModule(device_.GetDevice(), vertShaderModule, nullptr);
    vkDestroyShaderModule(device_.GetDevice(), fragShaderModule, nullptr);
    vkDestroyPipeline(device_.GetDevice(), graphicsPipeline, nullptr);
}

void Pipeline::Bind(VkCommandBuffer commandBuffer)
{
    vkCmdBindPipeline(
        commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
}

void Pipeline::CreateGraphicsPipeline(
    const std::string &vertFilePath,
    const std::string &fragFilePath,
    PipelineConfigInfo &configInfo)
{

    assert(
        configInfo.pipelineLayout != VK_NULL_HANDLE &&
        "无法创建pipeline : 无pipelineLayout");
    assert(
        configInfo.renderPass != VK_NULL_HANDLE &&
        "无法创建pipeline : 无renderPass");
    auto vertCode = ReadFile(vertFilePath);
    auto fragCode = ReadFile(fragFilePath);

    CreateShaderModule(vertCode, &vertShaderModule);
    CreateShaderModule(fragCode, &fragShaderModule);

    VkPipelineShaderStageCreateInfo shaderStages[2];
    shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    shaderStages[0].module              = vertShaderModule;
    shaderStages[0].pName               = "main";
    shaderStages[0].flags               = 0;
    shaderStages[0].pNext               = nullptr;
    shaderStages[0].pSpecializationInfo = nullptr;

    shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    shaderStages[1].module              = fragShaderModule;
    shaderStages[1].pName               = "main";
    shaderStages[1].flags               = 0;
    shaderStages[1].pNext               = nullptr;
    shaderStages[1].pSpecializationInfo = nullptr;

    auto bindingDescriptions   = Dxr::Mesh::Vertex::GetBindingDescriptions();
    auto attributeDescriptions = Dxr::Mesh::Vertex::GetAttributeDescriptions();

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType =
        VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexAttributeDescriptionCount =
        static_cast<uint32_t>(attributeDescriptions.size());
    vertexInputInfo.vertexBindingDescriptionCount =
        static_cast<uint32_t>(bindingDescriptions.size());
    vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();
    vertexInputInfo.pVertexBindingDescriptions   = bindingDescriptions.data();


    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType      = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages    = shaderStages;
    pipelineInfo.pVertexInputState   = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &configInfo.inputAssemblyInfo;
    pipelineInfo.pViewportState      = &configInfo.viewportInfo;
    pipelineInfo.pRasterizationState = &configInfo.rasterizationInfo;
    pipelineInfo.pMultisampleState   = &configInfo.multisampleInfo;
    pipelineInfo.pColorBlendState    = &configInfo.colorBlendInfo;
    pipelineInfo.pDepthStencilState  = &configInfo.depthStencilInfo;
    pipelineInfo.pDynamicState       = &configInfo.dynamicStateInfo;

    pipelineInfo.layout     = configInfo.pipelineLayout;
    pipelineInfo.renderPass = configInfo.renderPass;
    pipelineInfo.subpass    = configInfo.subpass;

    pipelineInfo.basePipelineIndex  = -1;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

    if(vkCreateGraphicsPipelines(
           device_.GetDevice(),
           VK_NULL_HANDLE,
           1,
           &pipelineInfo,
           nullptr,
           &graphicsPipeline) != VK_SUCCESS) {
        throw std::runtime_error("failed to create graphics pipeline");
    }
}

void Pipeline::CreateShaderModule(
    const std::vector<char> &code, VkShaderModule *shaderModule)
{
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode    = reinterpret_cast<const uint32_t *>(code.data());

    if(vkCreateShaderModule(
           device_.GetDevice(), &createInfo, nullptr, shaderModule) !=
       VK_SUCCESS) {
        throw std::runtime_error("failed to create shader module");
    }
}

void Pipeline::DefaultPipelineConfigInfo(PipelineConfigInfo &configInfo)
{

    configInfo.inputAssemblyInfo.sType =
        VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    configInfo.inputAssemblyInfo.topology =
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST; // 每三个顶点一个三角形（不共用顶点）
    configInfo.inputAssemblyInfo.primitiveRestartEnable = VK_FALSE;

    configInfo.viewportInfo.sType =
        VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    configInfo.viewportInfo.viewportCount =
        1; // 指定在管线创建时使用的视口数量，任何时候都可以动态地绑定更多的视口，但是需要在着色器中使用特殊的变量gl_ViewportIndex来选择视口
    configInfo.viewportInfo.pViewports =
        nullptr; // 指定指向视口数组的指针，如果动态设置视口，则可以将其设置为nullptr
    configInfo.viewportInfo.scissorCount =
        1; // 指定在管线创建时使用的裁剪矩形数量，任何时候都可以动态地绑定更多的裁剪矩形，但是需要在着色器中使用特殊的变量gl_ViewportIndex来选择裁剪矩形
    configInfo.viewportInfo.pScissors =
        nullptr; // 指定指向裁剪矩形数组的指针，如果动态设置裁剪矩形，则可以将其设置为nullptr

    // 配置光栅化
    configInfo.rasterizationInfo.sType =
        VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    configInfo.rasterizationInfo.depthClampEnable =
        VK_FALSE; // 对深度值使用clamp函数
    configInfo.rasterizationInfo.rasterizerDiscardEnable =
        VK_FALSE; // 光栅化之前丢弃所有图元
    configInfo.rasterizationInfo.polygonMode = VK_POLYGON_MODE_FILL;
    configInfo.rasterizationInfo.lineWidth   = 1.0f;
    configInfo.rasterizationInfo.cullMode = VK_CULL_MODE_NONE; // 背面剔除
    configInfo.rasterizationInfo.frontFace =
        VK_FRONT_FACE_CLOCKWISE; // 顺时针为正面
    configInfo.rasterizationInfo.depthBiasEnable         = VK_FALSE;
    configInfo.rasterizationInfo.depthBiasConstantFactor = 0.0f; // Optional
    configInfo.rasterizationInfo.depthBiasClamp          = 0.0f; // Optional
    configInfo.rasterizationInfo.depthBiasSlopeFactor    = 0.0f; // Optional

    // 配置MSAA抗锯齿
    configInfo.multisampleInfo.sType =
        VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    configInfo.multisampleInfo.sampleShadingEnable   = VK_FALSE;
    configInfo.multisampleInfo.rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT;
    configInfo.multisampleInfo.minSampleShading      = 1.0f;     // Optional
    configInfo.multisampleInfo.pSampleMask           = nullptr;  // Optional
    configInfo.multisampleInfo.alphaToCoverageEnable = VK_FALSE; // Optional
    configInfo.multisampleInfo.alphaToOneEnable      = VK_FALSE; // Optional

    configInfo.colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT |
        VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT |
        VK_COLOR_COMPONENT_A_BIT;
    configInfo.colorBlendAttachment.blendEnable = VK_FALSE;
    configInfo.colorBlendAttachment.srcColorBlendFactor =
        VK_BLEND_FACTOR_ONE; // Optional
    configInfo.colorBlendAttachment.dstColorBlendFactor =
        VK_BLEND_FACTOR_ZERO;                                       // Optional
    configInfo.colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
    configInfo.colorBlendAttachment.srcAlphaBlendFactor =
        VK_BLEND_FACTOR_ONE; // Optional
    configInfo.colorBlendAttachment.dstAlphaBlendFactor =
        VK_BLEND_FACTOR_ZERO;                                       // Optional
    configInfo.colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

    // alpha混合
    configInfo.colorBlendInfo.sType =
        VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    configInfo.colorBlendInfo.logicOpEnable   = VK_FALSE;
    configInfo.colorBlendInfo.logicOp         = VK_LOGIC_OP_COPY; // Optional
    configInfo.colorBlendInfo.attachmentCount = 1;
    configInfo.colorBlendInfo.pAttachments = &configInfo.colorBlendAttachment;
    configInfo.colorBlendInfo.blendConstants[0] = 0.0f; // Optional
    configInfo.colorBlendInfo.blendConstants[1] = 0.0f; // Optional
    configInfo.colorBlendInfo.blendConstants[2] = 0.0f; // Optional
    configInfo.colorBlendInfo.blendConstants[3] = 0.0f; // Optional

    // 深度测试
    configInfo.depthStencilInfo.sType =
        VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    configInfo.depthStencilInfo.depthTestEnable       = VK_TRUE;
    configInfo.depthStencilInfo.depthWriteEnable      = VK_TRUE;
    configInfo.depthStencilInfo.depthCompareOp        = VK_COMPARE_OP_LESS;
    configInfo.depthStencilInfo.depthBoundsTestEnable = VK_FALSE;
    configInfo.depthStencilInfo.minDepthBounds        = 0.0f; // Optional
    configInfo.depthStencilInfo.maxDepthBounds        = 1.0f; // Optional
    configInfo.depthStencilInfo.stencilTestEnable     = VK_FALSE;
    configInfo.depthStencilInfo.front                 = {}; // Optional
    configInfo.depthStencilInfo.back                  = {}; // Optional

    configInfo.dynamicStateEnables = {
        VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
    configInfo.dynamicStateInfo.sType =
        VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    configInfo.dynamicStateInfo.pDynamicStates =
        configInfo.dynamicStateEnables.data();
    configInfo.dynamicStateInfo.dynamicStateCount =
        static_cast<uint32_t>(configInfo.dynamicStateEnables.size());
    configInfo.dynamicStateInfo.flags = 0;
}
} // namespace Dxr
