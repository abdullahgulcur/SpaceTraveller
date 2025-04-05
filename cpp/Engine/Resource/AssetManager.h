#pragma once

#include "StaticMesh.h"
#include "TextureData.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "MeshData.h"

namespace Engine{

    class AssetManager{
    private:
    public:

        // vao cache
        std::map<std::string, MeshData> staticMeshDataCache;
        std::map<std::string, ShaderProgram> shaderProgramCache;
        std::map<std::string, Texture2D> texture2DCache;

        AssetManager(){}
        ~AssetManager(){}
        MeshData* loadStaticMeshDataTextured(std::string path, std::string key);
        ShaderProgram* loadShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath, std::string key);
        Texture2D* loadCompressedTexture2D(std::string path, std::string key);
        Texture2D* loadTexture2D(std::string path, std::string key);

    };
}
