#include "ShaderManager.h"
#include <iostream>
#include <sstream>
#include <fstream>

std::map<std::string, Shader> ShaderManager::_shaders;

Shader ShaderManager::LoadShader(
    const char* vShaderFile,
    const char* fShaderFile,
    const char* gShaderFile,
    const std::string& name)
{
    _shaders[name] = LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return _shaders[name];
}

Shader& ShaderManager::GetShader(const std::string& name)
{
    return _shaders[name];
}

void ShaderManager::Clear()
{
    // (properly) delete all shaders	
    for (const auto& iter : _shaders)
        glDeleteProgram(iter.second.GetID());
}

Shader ShaderManager::LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream;
        std::stringstream fShaderStream;

        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception& e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();

    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);

    return shader;
}
