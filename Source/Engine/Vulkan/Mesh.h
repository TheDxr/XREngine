#pragma once
#include "Device.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <vector>
namespace dxr
{

class Mesh
{
public:
    struct Vertex{
        glm::vec2 Position;
        static std::vector<VkVertexInputBindingDescription> GetBindingDescriptions();
        static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions();
    };
    Mesh(Device &device, const std::vector<Vertex> &vertices);
    ~Mesh();
    void bind(VkCommandBuffer commandBuffer);
    void draw(VkCommandBuffer commandBuffer);
private:
    void createVertexBuffer(const std::vector<Vertex> &vertices);
    Device &device_;
    VkBuffer vertexBuffer;
    //VkBuffer indexBuffer;
    VkDeviceMemory vertexBufferMemory;
   // VkDeviceMemory indexBufferMemory;
    uint32_t vertexCount;
};

} // namespace Dxr
