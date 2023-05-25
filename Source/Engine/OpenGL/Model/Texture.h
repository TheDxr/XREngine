#pragma once
#include <iostream>
#include <string>

#include "../Shader.h"
namespace dxr::gl
{
class Texture
{
public:
    Texture() = default;
    Texture(const std::string &path);
    void load(const std::string &path);
    void release();
    void bindTextureUniform(
        ShaderProgram &shaderProgram, const std::string &uniformName, unsigned int textureId);
    void bindTextureUniform(ShaderProgram &shaderProgram, const std::string &uniformName);
    bool empty() const { return empty_; }

    unsigned int id;
    std::string path;
    static constexpr int TEXTURE_UNIT_RANGE = 47;
    static unsigned int
        textureFromFile(const std::string &path, const std::string &directory, bool gamma = false);
    static void loadDefaultTexture();

private:
    bool empty_ = true;

    void load();
};
} // namespace dxr::gl