#include "Shader.h"

#include <vector>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <spdlog/spdlog.h>

using namespace std;
using namespace glm;

// file reading
void getFileContents(const char *filename, vector<char> &buffer)
{
    ifstream file(filename, ios_base::binary);
    if(file) {
        file.seekg(0, ios_base::end);
        streamsize size = file.tellg();
        if(size > 0) {
            file.seekg(0, ios_base::beg);
            buffer.resize(static_cast<size_t>(size));
            file.read(&buffer[0], size);
        }
        buffer.push_back('\0');
    }
    else {
        throw std::invalid_argument(string("The file ") + filename +
            " doesn't exists");
    }
}

Shader::Shader(const std::string &filename, GLenum type)
{
    // file loading
    vector<char> fileContent;
    getFileContents(filename.c_str(), fileContent);

    // creation
    mHandle = glCreateShader(type);
    if(mHandle == 0)
        throw std::runtime_error("Impossible to create a new Shader");

    // code source assignation
    const char *shaderText(&fileContent[0]);
    glShaderSource(mHandle, 1, (const GLchar **)&shaderText, NULL);

    // compilation
    glCompileShader(mHandle);

    // compilation check
    GLint compile_status;
    glGetShaderiv(mHandle, GL_COMPILE_STATUS, &compile_status);
    if(compile_status != GL_TRUE) {
        GLsizei logsize = 0;
        glGetShaderiv(mHandle, GL_INFO_LOG_LENGTH, &logsize);

        char *log = new char[logsize + 1];
        glGetShaderInfoLog(mHandle, logsize, &logsize, log);

        spdlog::error("compilation error:" + filename);
        spdlog::error(log);

        throw std::runtime_error("Impossible to compile Shader");
        //exit(EXIT_FAILURE);
    }
    else {
        spdlog::info("Shader " + filename + " compiled successfully");
    }
}

GLuint Shader::GetHandle() const
{
    return mHandle;
}

Shader::~Shader()
{
}

ShaderProgram::ShaderProgram()
{
    mHandle = glCreateProgram();
    if(!mHandle)
        throw std::runtime_error("Impossible to create a new shader program");
}

ShaderProgram::ShaderProgram(std::initializer_list<Shader> shaderList) :
    ShaderProgram()
{
    for(auto &s : shaderList)
        glAttachShader(mHandle, s.GetHandle());

    Link();
}

ShaderProgram::ShaderProgram(std::string vertexPath, std::string fragmentPath)
{
    Shader vertexShader(vertexPath, GL_VERTEX_SHADER);
    Shader fragmentShader(fragmentPath, GL_FRAGMENT_SHADER);
    mHandle = glCreateProgram();
    if(!mHandle)
        throw std::runtime_error("Impossible to create a new shader program");
    
    glAttachShader(mHandle, vertexShader.GetHandle());
    glAttachShader(mHandle, fragmentShader.GetHandle());

    Link();
}

void ShaderProgram::Link()
{
    glLinkProgram(mHandle);
    GLint result;
    glGetProgramiv(mHandle, GL_LINK_STATUS, &result);
    if(result != GL_TRUE) {
        spdlog::error("linkage error");


        GLsizei logsize = 0;
        glGetProgramiv(mHandle, GL_INFO_LOG_LENGTH, &logsize);

        char *log = new char[logsize];
        glGetProgramInfoLog(mHandle, logsize, &logsize, log);

        cout << log << endl;
    }
}

GLint ShaderProgram::Uniform(const std::string &name)
{
    auto it = mUniforms.find(name);
    if(it == mUniforms.end()) {
        // Uniform that is not referenced
        GLint r = glGetUniformLocation(mHandle, name.c_str());
        if(r == GL_INVALID_OPERATION || r < 0)
            spdlog::error("Uniform " + name + " doesn't exist in program");
        // add it anyways
        mUniforms[name] = r;

        return r;
    }
    else
        return it->second;
}

GLint ShaderProgram::Attribute(const std::string &name)
{
    GLint attrib = glGetAttribLocation(mHandle, name.c_str());
    if(attrib == GL_INVALID_OPERATION || attrib < 0)
        spdlog::error("Attribute " + name + " doesn't exist in program");

    return attrib;
}

void ShaderProgram::SetAttribute(const std::string &name,
                                 GLint size,
                                 GLsizei stride,
                                 const void *offset,
                                 GLboolean normalize,
                                 GLenum type)
{
    GLint loc = Attribute(name);
    glVertexAttribPointer(loc, size, type, normalize, stride,
                          offset);
    glEnableVertexAttribArray(loc);
}


void ShaderProgram::SetUniform(const std::string &name,
                               float x,
                               float y,
                               float z)
{
    glUniform3f(Uniform(name), x, y, z);
}

void ShaderProgram::SetUniform(const std::string &name, const vec3 &v)
{
    glUniform3fv(Uniform(name), 1, value_ptr(v));
}

void ShaderProgram::SetUniform(const std::string &name, const dvec3 &v)
{
    glUniform3dv(Uniform(name), 1, value_ptr(v));
}

void ShaderProgram::SetUniform(const std::string &name, const vec4 &v)
{
    glUniform4fv(Uniform(name), 1, value_ptr(v));
}

void ShaderProgram::SetUniform(const std::string &name, const dvec4 &v)
{
    glUniform4dv(Uniform(name), 1, value_ptr(v));
}

void ShaderProgram::SetUniform(const std::string &name, const dmat4 &m)
{
    glUniformMatrix4dv(Uniform(name), 1, GL_FALSE, value_ptr(m));
}

void ShaderProgram::SetUniform(const std::string &name, const mat4 &m)
{
    glUniformMatrix4fv(Uniform(name), 1, GL_FALSE, value_ptr(m));
}

void ShaderProgram::SetUniform(const std::string &name, const mat3 &m)
{
    glUniformMatrix3fv(Uniform(name), 1, GL_FALSE, value_ptr(m));
}

void ShaderProgram::SetUniform(const std::string &name, float val)
{
    glUniform1f(Uniform(name), val);
}

void ShaderProgram::SetUniform(const std::string &name, int val)
{
    glUniform1i(Uniform(name), val);
}

void ShaderProgram::SetUniform(const std::string &name, unsigned int val)
{
    glUniform1i(Uniform(name), val);
}

ShaderProgram::~ShaderProgram()
{
    // glDeleteProgram(mHandle);
}

void ShaderProgram::Use() const
{
    glUseProgram(mHandle);
}

void ShaderProgram::Unuse() const
{
    glUseProgram(0);
}

GLuint ShaderProgram::GetHandle() const
{
    return mHandle;
}
