#pragma once

#include <assimp/scene.h>
#include <vector>
#include <string>
#include <unordered_map>


#include "Material.h"
#include "Mesh.h"
namespace dxr::gl
{
class Model
{
public:
    explicit Model(const std::string &path);
    ~Model();
    //    Model(const Model&) = delete;
    //    Model& operator=(const Model&) = delete;
    void loadModel(const std::string &path);

    // Uniform("material.diffuse")
    // Uniform("material.specular")
    // Uniform("material.shininess")
    void draw(ShaderProgram &shader);

    std::string directory;
    // stores all the textures path loaded so far, optimization to make sure textures
    std::unordered_map<std::string, bool> texturesLoaded;

    std::vector<Mesh> meshes;
    bool GammaCorrection;

private:
    void loadMaterials(aiMaterial *material, Material &materialStruct);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    Texture loadMaterialTextures(aiMaterial *mat, aiTextureType type);
    void loadMaterialTextures(aiMaterial *mat, aiTextureType type, Texture &texture);
};
}