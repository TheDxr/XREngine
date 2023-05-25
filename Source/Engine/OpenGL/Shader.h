#pragma once

#define GLM_FORCE_RADIANS

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <initializer_list>
#include <map>
#include <string>

namespace dxr::gl
{
class ShaderProgram;

class Shader;

// Loads a shader from a file into OpenGL.
class Shader
{
public:
    // Load Shader from a file
    Shader(const std::string &filename, GLenum type);

    Shader() = default;

    // provide opengl shader identifiant.
    GLuint getHandle() const;

    ~Shader();

private:
    // opengl program identifiant
    GLuint handle;

    friend class ShaderProgram;
};

// A shader program is a set of shader (for instance vertex shader + pixel
// shader) defining the rendering pipeline.
//
// This class provide an interface to define the OpenGL mUniforms and mAttributes
// using GLM objects.
class ShaderProgram
{
public:
    // constructor
    ShaderProgram(std::initializer_list<Shader> shaderList);

    ShaderProgram(std::string vertexPath, std::string fragmentPath);

    // bind the program
    void use() const;

    void unuse() const;

    // provide the opengl identified
    GLuint getHandle() const;


    // provide mAttributes information.
    GLint attribute(const std::string &name);

    void setAttribute(
        const std::string &name,
        GLint size,
        GLsizei stride,
        const void *offset  = reinterpret_cast<void *>(0),
        GLboolean normalize = GL_FALSE,
        GLenum type         = GL_FLOAT);


    // provide Uniform location
    GLint uniform(const std::string &name);

    // affect Uniform
    void setUniform(const std::string &name, float x, float y, float z);

    void setUniform(const std::string &name, const glm::vec3 &v);

    void setUniform(const std::string &name, const glm::dvec3 &v);

    void setUniform(const std::string &name, const glm::vec4 &v);

    void setUniform(const std::string &name, const glm::dvec4 &v);

    void setUniform(const std::string &name, const glm::dmat4 &m);

    void setUniform(const std::string &name, const glm::mat4 &m);

    void setUniform(const std::string &name, const glm::mat3 &m);

    void setUniform(const std::string &name, float val);

    void setUniform(const std::string &name, int val);

    void setUniform(const std::string &name, unsigned int val);

    ~ShaderProgram();


private:
    ShaderProgram();

    std::map<std::string, GLint> uniforms;
    std::map<std::string, GLint> attributes;

    // opengl id
    GLuint handle;

    void link();
};
} // namespace dxr::gl