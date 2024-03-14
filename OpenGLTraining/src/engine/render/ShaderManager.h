#pragma once
#include "Shader.h"
#include "Texture.h"
#include <map>
#include <string>

class ShaderManager
{
public:
    // loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
    static Shader LoadShader(
        const char* vShaderFile,
        const char* fShaderFile,
        const char* gShaderFile,
        const std::string& name);
    
    // retrieves a stored sader
    static Shader& GetShader(const std::string& name);

    // properly de-allocates all loaded resources
    static void Clear();

private:
    static std::map<std::string, Shader> _shaders;

    // loads and generates a shader from file
    static Shader LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
    
    // loads a single texture from file
    static Texture LoadTextureFromFile(const char* file, bool alpha);
};
