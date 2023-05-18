#pragma once
#include "Shader.h"

#include "Material.h"
#include <glm/glm.hpp>

#include <vector>

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh
{
public:
    Mesh(const std::vector<Vertex>& vertices,const  std::vector<unsigned int>& indices, 
        const Material& material);
    Mesh();
    ~Mesh();
    void draw(ShaderProgram& shaderProgram);
private:
    unsigned int VAO, VBO, EBO;
    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndices;
    Material mMaterial;
    void setupMesh();
};
