#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

#include "stb_image/stb_image.h"

// Instantiate static variables
std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;
std::string ResourceManager::m_FullPath = std::filesystem::current_path().string() + "/";

Shader ResourceManager::LoadShader(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& gShaderFile, std::string name)
{

    std::string _vShaderFile = m_FullPath + vShaderFile;
    std::string _fShaderFile = m_FullPath + fShaderFile;
    std::string _gShaderFile = "";
    if (!gShaderFile.empty())
        std::string _gShaderFile = m_FullPath + gShaderFile;

    Shaders[name] = loadShaderFromFile(_vShaderFile.c_str(), _fShaderFile.c_str(), !_gShaderFile.empty()? _gShaderFile.c_str() : nullptr);
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const std::string& file, bool alpha, std::string name)
{
    std::string _tex = m_FullPath + file;
    
    Textures[name] = loadTextureFromFile(_tex.c_str(), alpha);
    return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

void ResourceManager::Clear()
{
    // (properly) delete all shaders	
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID());
    // (properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID());
}

Shader ResourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

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

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    const char *gShaderCode = geometryCode.c_str();

    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char *file, bool alpha)
{
    Texture2D texture;
    if (alpha)
    {
        texture.InternalFormat() = GL_RGBA;
        texture.ImageFormat() = GL_RGBA;
    }

    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

    if (!data)
    {
        std::cout << "ERROR::TEXTURE: Failed to load texture" << std::endl;
        
        // TODO throw an exception if exceptions are enabled
        
        return texture;
    }

    texture.Generate(width, height, data);

    stbi_image_free(data);
    return texture;
}