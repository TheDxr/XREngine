#pragma once
#include <string>
#include <iostream>

#include "Shader.h"
class Texture
{
public:
    Texture() = default;
    Texture(const std::string& path);
    void Load(const std::string& path);
    void Release();
    void BindTextureUniform(ShaderProgram& shaderProgram, const std::string& uniformName, unsigned int textureId);
    void BindTextureUniform(ShaderProgram& shaderProgram, const std::string& uniformName);
    [[nodiscard]] bool IsEmpty() const { return mEmpty; }

    unsigned int Id;
    std::string Path;

    static unsigned int TextureFromFile(const std::string &path, const std::string &directory, bool gamma = false);
    static void LoadDefaultTexture();
private:
    bool mEmpty = true;
    static constexpr int TextureUnitRange = 47;
    void load();
};
