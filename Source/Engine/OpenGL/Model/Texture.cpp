#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/glad.h>
#include "spdlog/spdlog.h"
namespace dxr::gl
{
using namespace std;

Texture::Texture(const std::string &path) : path(path)
{
    load();
    empty_ = false;
}


void Texture::load()
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    if(data) {
        GLenum format{};
        if(nrComponents == 1)
            format = GL_RED;
        else if(nrComponents == 3)
            format = GL_RGB;
        else if(nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        id = textureID;
        spdlog::info("Texture id: " + to_string(textureID) + " load at path: " + path);
        stbi_image_free(data);
    }
    else {
        spdlog::error("Texture failed to load at path: " + path);
        stbi_image_free(data);
    }
}

void Texture::bindTextureUniform(
    ShaderProgram &shaderProgram, const string &uniformName, unsigned int textureId)
{
    if(textureId > TEXTURE_UNIT_RANGE) {
        spdlog::error("Texture unit is out of range");
        return;
    }
    if(empty_) {
        spdlog::error("Texture unit is Empty");
        return;
    }
    glActiveTexture(GL_TEXTURE0 + textureId);
    shaderProgram.setUniform(uniformName, textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::bindTextureUniform(ShaderProgram &shaderProgram, const string &uniformName)
{
    if(id > TEXTURE_UNIT_RANGE) {
        spdlog::error("Texture unit is out of range");
        return;
    }
    glActiveTexture(GL_TEXTURE0 + id);
    shaderProgram.setUniform(uniformName, id);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::load(const string & filePath)
{
    path = filePath;
    load();
    empty_ = false;
}

void Texture::release()
{
    // TODO: Implement this
}

void Texture::loadDefaultTexture()
{
    int width, height, nrComponents;
    unsigned char *data = stbi_load(
        "D:/SourceCode/CppCode/OpenGL/Assets/Textures/default.png",
        &width,
        &height,
        &nrComponents,
        0);
    if(data) {
        GLenum format{};
        if(nrComponents == 1)
            format = GL_RED;
        else if(nrComponents == 3)
            format = GL_RGB;
        else if(nrComponents == 4)
            format = GL_RGBA;
        glBindTexture(GL_TEXTURE_2D, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        //        glGenerateMipmap(GL_TEXTURE_2D);
        //
        //        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        //        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        //        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        spdlog::info("Texture id: " + to_string(0) + " load at path: default");
        stbi_image_free(data);
    }
    else {
        spdlog::error("default Texture failed to load");
        stbi_image_free(data);
    }
}

unsigned int Texture::textureFromFile(const std::string &path, const string &directory, bool gamma)
{
    string filename = string(path);
    filename        = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if(data) {
        GLenum format{};
        if(nrComponents == 1)
            format = GL_RED;
        else if(nrComponents == 3)
            format = GL_RGB;
        else if(nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        spdlog::info("Texture id: " + to_string(textureID) + " load at path: " + path);
        stbi_image_free(data);
    }
    else {
        spdlog::error("Texture failed to load at path: " + path);
        stbi_image_free(data);
    }

    return textureID;
}
} // namespace OpenGL