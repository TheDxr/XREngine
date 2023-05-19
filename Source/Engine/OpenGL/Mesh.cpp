#include "Mesh.h"

#include <glad/glad.h>

#include <vector>
using namespace std;

Mesh::Mesh(const std::vector<Vertex>& vertices,const std::vector<unsigned>& indices,const Material& material) :
    mVertices(vertices), mIndices(indices), mMaterial(material)
{
    setupMesh();
}

Mesh::Mesh()
{
    // 硬编码mesh
    // -------------------------
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
        -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

        -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, -1.0f, 0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f, -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  1.0f, 1.0f,
        0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f, 1.0f,

        -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f};
    for(int i = 0; i < 36; i++) {
        mVertices.emplace_back(Vertex({
            {vertices[i * 8], vertices[i * 8 + 1], vertices[i * 8 + 2]},
            { vertices[i * 8 + 3],vertices[i * 8 + 4], vertices[i * 8 + 5]},
            { vertices[i * 8 + 6], vertices[i * 8 + 7]}}));
    }
    mIndices = {0,  1,  3,  1,  2,  3,  4,  5,  7,  5,  6,  7,  8,  9,  11, 9,  10, 11, 12, 13, 15, 13, 14, 15,
           16, 17, 19, 17, 18, 19, 20, 21, 23, 21, 22, 23};
    setupMesh();
}

Mesh::~Mesh()
{
}

void Mesh::draw(ShaderProgram &shaderProgram)
{
    auto diffuseId = mMaterial.Diffuse.Id;
    auto specularId = mMaterial.Specular.Id;
    shaderProgram.SetUniform("objRawColor", mMaterial.RawColor);
    if(diffuseId != 0)mMaterial.Diffuse.BindTextureUniform(shaderProgram, "material.diffuse");
    if(specularId != 0)mMaterial.Specular.BindTextureUniform(shaderProgram, "material.specular");
    if(specularId != 0)shaderProgram.SetUniform("material.shininess", mMaterial.Shininess);

//    if(diffuseId != 0) {
//        glActiveTexture(GL_TEXTURE0 + diffuseId);
//        shaderProgram.SetUniform("material.diffuse", diffuseId);
//        glBindTexture(GL_TEXTURE_2D, diffuseId);
//    }
//
//    if(specularId != 0) {
//        glActiveTexture(GL_TEXTURE0 + specularId);
//        shaderProgram.SetUniform("material.specular", specularId);
//        glBindTexture(GL_TEXTURE_2D, specularId);
//    }
        
    

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh()
{
    // create VBO VAO EBO
    // -------------------------
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mVertices.size(), &mVertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mIndices.size(), &mIndices[0], GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(mVertices), (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(mVertices), (void *)(3 * sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(mVertices), (void *)(6 * sizeof(float)));

    // unbind
    // glBindVertexArray(0);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
}
