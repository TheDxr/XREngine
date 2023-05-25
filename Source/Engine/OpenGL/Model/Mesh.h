#pragma once
#include "../Shader.h"

#include <glm/glm.hpp>
#include "Material.h"

#include <vector>

namespace dxr::gl
{
struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};
class Mesh
{
public:
    Mesh(
        const std::vector<Vertex> &vertices,
        const std::vector<unsigned int> &indices,
        const Material &material);
    Mesh();
    ~Mesh();
    void draw(ShaderProgram &shaderProgram);

private:
    unsigned int VAO, VBO, EBO;
    std::vector<Vertex> vertices_;
    std::vector<unsigned int> indices_;
    Material material_;
    void setupMesh();
};
} // namespace dxr::gl