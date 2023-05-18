#pragma once

#define GLM_FORCE_RADIANS
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <initializer_list>
#include <map>
#include <string>

class Shader;
class ShaderProgram;

// Loads a shader from a file into OpenGL.
class Shader
{
public:
    // Load Shader from a file
    Shader(const std::string& filename, GLenum type);
    Shader() = default;
    // provide opengl shader identifiant.
    GLuint GetHandle() const;

    ~Shader();

private:
    // opengl program identifiant
    GLuint mHandle;

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
    void Use() const;
    void Unuse() const;

    // provide the opengl identified
    GLuint GetHandle() const;


    // provide mAttributes information.
    GLint Attribute(const std::string& name);
    void SetAttribute(const std::string& name, GLint size, GLsizei stride,
                      const void* offset = reinterpret_cast<void*>(0),
                      GLboolean normalize = GL_FALSE, GLenum type = GL_FLOAT);


    // provide Uniform location
    GLint Uniform(const std::string& name);

    // affect Uniform
    void SetUniform(const std::string& name, float x, float y, float z);
    void SetUniform(const std::string& name, const glm::vec3& v);
    void SetUniform(const std::string& name, const glm::dvec3& v);
    void SetUniform(const std::string& name, const glm::vec4& v);
    void SetUniform(const std::string& name, const glm::dvec4& v);
    void SetUniform(const std::string& name, const glm::dmat4& m);
    void SetUniform(const std::string& name, const glm::mat4& m);
    void SetUniform(const std::string& name, const glm::mat3& m);
    void SetUniform(const std::string& name, float val);
    void SetUniform(const std::string& name, int val);
    void SetUniform(const std::string& name, unsigned int val);
    ~ShaderProgram();
    

private:
    ShaderProgram();

    std::map<std::string, GLint> mUniforms;
    std::map<std::string, GLint> mAttributes;

    // opengl id
    GLuint mHandle;

    void Link();
};
