#include "pch.h"
#include "AssetManager.h"
#include "TextureData.h"

namespace Engine{

//    MeshData* AssetManager::loadStaticMeshDataTextured(std::string path, std::string key){
//
//        MeshData meshData;
//        meshData.loadStaticMeshTextured(path);
//        staticMeshDataCache[key] = meshData;
//        return &staticMeshDataCache[key];
//    }
//
//    ShaderProgram* AssetManager::loadShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath, std::string key){
//
//        ShaderProgram shaderProgram(vertexShaderPath, fragmentShaderPath);
//        shaderProgramCache[key] = shaderProgram;
//        return &shaderProgramCache[key];
//    }
//
//    Texture2D* AssetManager::loadCompressedTexture2D(std::string path, std::string key) {
//
//        CompressedTextureData2D data(path);
//        Texture2D tex(data.buffer, data.width, data.height, data.blockDimension);
//        texture2DCache[key] = tex;
//        return &texture2DCache[key];
//    }
//
//    Texture2D* AssetManager::loadTexture2D(std::string path, unsigned int desiredChannels, std::string key) {
//
//        TextureData2D data(path, desiredChannels);
//        Texture2D tex(data.data, data.width, data.height, data.channels);
//        texture2DCache[key] = tex;
//        return &texture2DCache[key];
//    }

//    void AssetManager::loadBillboardMesh(std::string key){
//
//        float vertices[] = {
//                -0.5f, -0.5f,
//                0.5f, -0.5f,
//                -0.5f,  0.5f,
//                0.5f,  0.5f,
//        };
//
//        VertexBuffer::VertexBuffer billboardVertexBuffer;
//        VertexBuffer::generate(billboardVertexBuffer.bufferId);
//        VertexBuffer::bufferData(billboardVertexBuffer.bufferId, sizeof(vertices), &vertices[0]);
//        vertexBufferCache[key] = billboardVertexBuffer;
//        return &vertexBufferCache[key];
//    }

//    void AssetManager::loadStaticMeshDataTextured(MeshData& meshData, std::string path){
//
//        meshData.loadStaticMeshTextured(path);
//    }
//
//    void AssetManager::loadShaderProgram(ShaderProgram& program, std::string vertexShaderPath, std::string fragmentShaderPath){
//
//        program(vertexShaderPath, fragmentShaderPath);
//    }
//
//    void AssetManager::loadCompressedTexture2D(Texture2D& tex, std::string path) {
//
//        CompressedTextureData2D data(path);
//        Texture2D tex(data.buffer, data.width, data.height, data.blockDimension);
//        texture2DCache[key] = tex;
//        return &texture2DCache[key];
//    }
//
//    void AssetManager::loadTexture2D(Texture2D& tex, std::string path, unsigned int desiredChannels) {
//
//        TextureData2D data(path, desiredChannels);
//        Texture2D tex(data.data, data.width, data.height, data.channels);
//        texture2DCache[key] = tex;
//        return &texture2DCache[key];
//    }
//
//    void AssetManager::loadBillboardMesh(unsigned int& vertexBuffer){
//
//        float vertices[] = {
//                -0.5f, -0.5f,
//                0.5f, -0.5f,
//                -0.5f,  0.5f,
//                0.5f,  0.5f,
//        };
//
//        VertexBuffer::generate(vertexBuffer,  sizeof(vertices), &vertices[0]);
//    }
//
//    void AssetManager::loadQuadMesh(unsigned int& vertexBuffer){
//        float vertices[] = {
//                -1.f, -1.f,
//                1.f, -1.f,
//                -1.f,  1.f,
//                1.f,  1.f,
//        };
//
//        VertexBuffer::generate(vertexBuffer,  sizeof(vertices), &vertices[0]);
//    }


}
