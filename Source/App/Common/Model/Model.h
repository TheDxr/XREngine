#pragma once

#include <assimp/scene.h>
#include <vector>
#include <string>
#include <unordered_map>

#include "../Entity.h"
#include "OpenGL/Material.h"
#include "OpenGL/Mesh.h"

class Model : public Entity
{
public:
	explicit Model(const std::string& path);
	~Model();
//    Model(const Model&) = delete;
//    Model& operator=(const Model&) = delete;
	void loadModel(const std::string& path);

    //Uniform("material.diffuse")
    //Uniform("material.specular")
    //Uniform("material.shininess")
    void Render(ShaderProgram &shader);

    std::string Directory;
    // stores all the textures path loaded so far, optimization to make sure textures
    std::unordered_map<std::string, bool> TexturesLoaded; 

    std::vector<Mesh> Meshes;
    bool GammaCorrection;
private:
    void LoadMaterials(aiMaterial *material,Material& materialStruct);
    void ProcessNode(aiNode *node, const aiScene *scene);
    Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
    [[deprecated]]Texture LoadMaterialTextures(aiMaterial *mat, aiTextureType type);
    void LoadMaterialTextures(aiMaterial *mat, aiTextureType type ,Texture &texture);
};
