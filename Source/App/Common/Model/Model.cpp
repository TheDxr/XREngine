#include "Model.h"
#include "Material.h"
#include "Texture.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <spdlog/spdlog.h>


using namespace std;

Model::Model(const std::string &path) { loadModel(path); }

Model::~Model() {}

void Model::loadModel(const std::string &path)
{
    Directory = path.substr(0, path.find_last_of('/'));
    auto type = path.substr(path.find_last_of('.') + 1, path.size() - path.find_last_of('.') - 1);
    Assimp::Importer importer;
    if(type == "obj") {
        const aiScene *scene =
            importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
        if(!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
            spdlog::error("ERROR::ASSIMP::" + std::string(importer.GetErrorString()));
            return;
        }
        ProcessNode(scene->mRootNode, scene);
    }
    else {
        const aiScene *scene = importer.ReadFile(path,
                                                 aiProcess_CalcTangentSpace | aiProcess_Triangulate |
                                                     aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
        if(!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
            spdlog::error("ERROR::ASSIMP::" + std::string(importer.GetErrorString()));
            return;
        }
        ProcessNode(scene->mRootNode, scene);
    }
}

void Model::Render(ShaderProgram &shader)
{
    for(unsigned int i = 0; i < Meshes.size(); i++)
        Meshes[i].draw(shader);
}

void Model::ProcessNode(aiNode *node, const aiScene *scene)
{
    // process each mesh located at the current node
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        Meshes.emplace_back(ProcessMesh(mesh, scene));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene);
    }
}


Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
    // data to fill
    vector<Vertex> vertices;
    vector<unsigned int> indices;

    // walk through each of the mesh's vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex tempVertex;
        glm::vec3
            vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly
        // convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x            = mesh->mVertices[i].x;
        vector.y            = mesh->mVertices[i].y;
        vector.z            = mesh->mVertices[i].z;
        tempVertex.Position = vector;
        // normals
        if(mesh->HasNormals()) {
            vector.x          = mesh->mNormals[i].x;
            vector.y          = mesh->mNormals[i].y;
            vector.z          = mesh->mNormals[i].z;
            tempVertex.Normal = vector;
        }
        // texture coordinates
        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 tempVec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // Use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            tempVec.x            = mesh->mTextureCoords[0][i].x;
            tempVec.y            = mesh->mTextureCoords[0][i].y;
            tempVertex.TexCoords = tempVec;
            // tangent
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            // TODO: Fix this
            // vertex.Tangent = vector;
            // bitangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            // vertex.Bitangent = vector;
        }
        else
            tempVertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.emplace_back(tempVertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex
    // indices.
    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    Material tempMaterial{};
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    std::pair<aiTextureType, Texture &> texturePair[]{{aiTextureType_DIFFUSE, tempMaterial.Diffuse},
                                                      {aiTextureType_SPECULAR, tempMaterial.Specular},
                                                      {aiTextureType_HEIGHT, tempMaterial.Normal},
                                                      {aiTextureType_AMBIENT, tempMaterial.Height}};

    for(auto pairItem : texturePair) {
        if(material->GetTextureCount(pairItem.first) == 0) {
            aiColor3D color;
            material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
            tempMaterial.RawColor = glm::vec3(color.r, color.g, color.b);
        }
        else {
            LoadMaterialTextures(material, pairItem.first, pairItem.second);
        }
    }

    //    LoadMaterialTextures(material, aiTextureType_SPECULAR, tempMaterial.Specular);
    //    LoadMaterialTextures(material, aiTextureType_HEIGHT, tempMaterial.Normal);
    //    LoadMaterialTextures(material, aiTextureType_AMBIENT, tempMaterial.Height);
    // return a mesh object created from the extracted mesh data
    return {vertices, indices, tempMaterial};
}


// 检查给定类型的所有材质纹理，如果尚未加载则加载纹理。
// 所需信息作为纹理结构返回。
Texture Model::LoadMaterialTextures(aiMaterial *mat, aiTextureType type)
{
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str); // 获取每个纹理的文件位置，它会将结果储存在一个aiString中
        string texturePath = string(str.C_Str());

        // 检查之前是否加载了纹理
        if(!TexturesLoaded[texturePath]) {
            TexturesLoaded.emplace(make_pair(texturePath, true));
            return {string(this->Directory + "/" + texturePath)};
        }
    }
    return {};
}
void Model::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, Texture &texture)
{
    const int textureCount = mat->GetTextureCount(type);
    if(textureCount == 0) {
    }
    else
        for(unsigned int i = 0; i < textureCount; i++) {
            aiString str;
            mat->GetTexture(type, i, &str); // 获取每个纹理的文件位置，它会将结果储存在一个aiString中
            string texturePath = string(str.C_Str());
            // 检查之前是否加载了纹理
            if(!TexturesLoaded[texturePath]) {
                TexturesLoaded.emplace(make_pair(texturePath, true));
                texture.Load(string(this->Directory + "/" + texturePath));
            }
        }
}
