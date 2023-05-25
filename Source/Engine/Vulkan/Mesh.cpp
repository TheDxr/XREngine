#include "Mesh.h"

#include <cassert>
#include <cstring>
namespace dxr
{
Mesh::Mesh(Device &device, const std::vector<Vertex> &vertices) : device_(device) {
    createVertexBuffer(vertices); }
void Mesh::bind(VkCommandBuffer commandBuffer)
{
    VkBuffer buffers[] = {vertexBuffer};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
}
void Mesh::createVertexBuffer(const std::vector<Vertex> &vertices)
{
    vertexCount = static_cast<uint32_t>(vertices.size());
    assert(vertexCount >= 3 && "Vertex count must be at least 3 (triangle)");
    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();
    device_.createBuffer(bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                         VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, vertexBuffer,
                         vertexBufferMemory);

    void *data;
    vkMapMemory(device_.getDevice(), vertexBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
    vkUnmapMemory(device_.getDevice(), vertexBufferMemory);
//    device_.CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
//                         VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);
//    device_.CopyBuffer(stagingBuffer, vertexBuffer, bufferSize);
//    vkDestroyBuffer(device_.GetDevice(), stagingBuffer, nullptr);
//    vkFreeMemory(device_.GetDevice(), stagingBufferMemory, nullptr);
}
void Mesh::draw(VkCommandBuffer commandBuffer)
{
    vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
}
Mesh::~Mesh()
{
    vkDestroyBuffer(device_.getDevice(), vertexBuffer, nullptr);
    vkFreeMemory(device_.getDevice(), vertexBufferMemory, nullptr);
//    vkDestroyBuffer(device_.GetDevice(), indexBuffer, nullptr);
//    vkFreeMemory(device_.GetDevice(), indexBufferMemory, nullptr);
}
std::vector<VkVertexInputAttributeDescription> Mesh::Vertex::GetAttributeDescriptions()
{
    std::vector<VkVertexInputAttributeDescription> attributeDescriptions(1);
    attributeDescriptions[0].binding  = 0;
    attributeDescriptions[0].location = 0; // layout (location = 0) in vec2  position;
    attributeDescriptions[0].format   = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptions[0].offset   = offsetof(Vertex, Position);
    return attributeDescriptions;
}
std::vector<VkVertexInputBindingDescription> Mesh::Vertex::GetBindingDescriptions()
{
    std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
    bindingDescriptions[0].binding   = 0;
    bindingDescriptions[0].stride    = sizeof(Vertex);
    bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    return bindingDescriptions;
}
} // namespace Dxr