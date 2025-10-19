#include "pch.h"
#include "AssetGenerator.h"

#include "Texture2D.h"
#include "FrameBuffer.h"
#include "VertexBuffer.h"
#include "Vao.h"
#include "DrawCommand.h"
//#include "AssetManager.h"
//#include "stb_image.h"

namespace Game {

	void AssetGenerator::init() {

        // sounds etc.
	}

    void AssetGenerator::initRenderObjects() {

        Engine::VertexBuffer::generateBillboardVertexBuffer(vertexBufferBillboard);
        Engine::VertexBuffer::generateQuadVertexBuffer(vertexBufferQuad);

        Engine::VertexBuffer::generate(instanceBufferParticleDynamic, 16384, nullptr);
        Engine::VertexBuffer::generate(instanceBufferTerrain, 1224, nullptr); // level [0,10] her biri 4 byte, 36 + 27 * 9

        AssetGenerator::createParticleMeshSolarSystemVao(vaoParticleSolarSystem, vertexBufferBillboard, instanceBufferParticleDynamic);
        Engine::Vao::createQuadMeshVao(quadVAO, vertexBufferQuad);

        Shader::createShader(shaderSun);
        Shader::createShader(shaderParticleSolarSystem);

        Engine::MeshData::generateQuadSphereMeshTextured(sphereMeshData);
        Engine::MeshData::generateTerrainBlockMesh(terrainBlockMeshData, 16);
        Engine::MeshData::generateTerrainOuterDegenerateMesh(terrainOuterDegenerateMeshData, 16);
        AssetGenerator::createTerrainMeshVao(vaoTerrainBlock, terrainBlockMeshData.vertexBuffer, terrainBlockMeshData.indexBuffer.bufferId, instanceBufferTerrain);
        AssetGenerator::createTerrainMeshVao(vaoTerrainOuterDegenerate, terrainOuterDegenerateMeshData.vertexBuffer, terrainOuterDegenerateMeshData.indexBuffer.bufferId, instanceBufferTerrain);

        Engine::Vao::createLitMeshTexturedVao(vaoSphereMesh, sphereMeshData.vertexBuffer, sphereMeshData.indexBuffer.bufferId);
        Shader::createShader(planetShader);
        Engine::Texture::createTexture2D(perlinTextureId, "texture/noise/perlin.jpg");
        Engine::Texture::createTexture2D(macroTextureId, "texture/noise/macro.jpg");

        std::vector<std::string> pathList = {
            "texture/noise/octave.jpg",
            "texture/noise/macro.jpg",
            "texture/noise/rock.jpg",
            "texture/noise/rocky.jpg",
            "texture/noise/soil.jpg",
            "texture/noise/stone.jpg",
            "texture/noise/grass.jpg"
        };
        Engine::Texture::createTextureArray2D(noiseTextureArrayId, pathList);

        Shader::createShader(shaderTerrain);

        AssetGenerator::generateSunBillboardTexture();
    }


    //TODO: burdaki vao, vbo gibi seyler genelde kullaniliyor. olusturup sildirmek gereksiz is yuku
	void AssetGenerator::generateSunBillboardTexture() {

        unsigned int noiseTextureId;
        Engine::Texture::createTexture2D(noiseTextureId, "texture/noise.jpg");

        Engine::Texture::Texture2DConfig sunTexConfig;
        sunTexConfig.width = 64;
        sunTexConfig.height = 64;
        sunTexConfig.internalFormat = GL_RGBA8;
        sunTexConfig.format = GL_RGBA;

        Engine::Texture::createTexture2D(sunFarBillboardTextureId, sunTexConfig);

        unsigned int fbo;
        Engine::FrameBuffer::generateFbo(fbo, sunFarBillboardTextureId, GL_COLOR_ATTACHMENT0);

        Shader::ShaderTextureGeneratorSun program;
        Shader::createShader(program);

        glViewport(0, 0, 64, 64);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glDisable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT);

        Engine::Shader::uniformTexture(program.loc_Tex, 0, noiseTextureId);

        unsigned int vb;
        Engine::VertexBuffer::generateQuadVertexBuffer(vb);

        unsigned int vao;
        Engine::Vao::createQuadMeshVao(vao, vb);

        Engine::DrawCommand::drawQuad(vao);

        Engine::Texture::mipmapTex2D(sunFarBillboardTextureId);

        Engine::VertexBuffer::clear(vb);
        Engine::Vao::deleteVao(vao);
        Engine::Shader::deleteShaderProgram(program.programId);
        Engine::Texture::clearTex(noiseTextureId);
        Engine::FrameBuffer::deleteFbo(fbo);
	}

    // -------------- VAO --------------

    void AssetGenerator::createParticleMeshVao(unsigned int& vao, unsigned int vertexBufferId, unsigned int instanceBufferId) {
        Engine::Vao::generate(vao);
        Engine::Vao::bind(vao);
        Engine::VertexBuffer::bind(vertexBufferId);
        Engine::Vao::vertexAttributePointer(0, 2, GL_FLOAT, 8, 0);
        Engine::VertexBuffer::bind(instanceBufferId);
        Engine::Vao::vertexAttributeIntegerPointerInstanced(1, 1, GL_UNSIGNED_SHORT, sizeof(ParticleSystem::ParticleGPUData), 0);
        Engine::Vao::vertexAttributeIntegerPointerInstanced(2, 3, GL_SHORT, sizeof(ParticleSystem::ParticleGPUData), 2);
        Engine::Vao::vertexAttributeIntegerPointerInstanced(3, 3, GL_BYTE, sizeof(ParticleSystem::ParticleGPUData), 8);
        Engine::Vao::vertexAttributePointerInstancedNormalized(4, 4, GL_UNSIGNED_BYTE, sizeof(ParticleSystem::ParticleGPUData), 11);
        Engine::Vao::vertexAttributeIntegerPointerInstanced(5, 1, GL_UNSIGNED_BYTE, sizeof(ParticleSystem::ParticleGPUData), 15);
        Engine::Vao::unbind();
    }

    void AssetGenerator::createParticleMeshSolarSystemVao(unsigned int& vao, unsigned int vertexBufferId, unsigned int instanceBufferId) {
        Engine::Vao::generate(vao);
        Engine::Vao::bind(vao);
        Engine::VertexBuffer::bind(vertexBufferId);
        Engine::Vao::vertexAttributePointer(0, 2, GL_FLOAT, 8, 0);
        Engine::VertexBuffer::bind(instanceBufferId);
        Engine::Vao::vertexAttributeIntegerPointerInstanced(1, 3, GL_SHORT, sizeof(ParticleSystem::ParticleGPUDataSolarSystem), 0);
        Engine::Vao::vertexAttributeIntegerPointerInstanced(2, 1, GL_UNSIGNED_BYTE, sizeof(ParticleSystem::ParticleGPUDataSolarSystem), 6);
        Engine::Vao::vertexAttributeIntegerPointerInstanced(3, 1, GL_UNSIGNED_BYTE, sizeof(ParticleSystem::ParticleGPUDataSolarSystem), 7);
        Engine::Vao::unbind();
    }

    void AssetGenerator::createGalaxyMeshVao(unsigned int& vao, unsigned int vertexBufferId, unsigned int instanceBufferId) {
        Engine::Vao::generate(vao);
        Engine::Vao::bind(vao);
        Engine::VertexBuffer::bind(vertexBufferId);
        Engine::Vao::vertexAttributePointer(0, 2, GL_FLOAT, 8, 0);
        Engine::VertexBuffer::bind(instanceBufferId);
        Engine::Vao::vertexAttributePointerInstanced(1, 4, GL_FLOAT, 80, 0);
        Engine::Vao::vertexAttributePointerInstanced(2, 4, GL_FLOAT, 80, 16);
        Engine::Vao::vertexAttributePointerInstanced(3, 4, GL_FLOAT, 80, 32);
        Engine::Vao::vertexAttributePointerInstanced(4, 4, GL_FLOAT, 80, 48);
        Engine::Vao::vertexAttributePointerInstanced(5, 4, GL_FLOAT, 80, 64);
        Engine::Vao::unbind();
    }

    void AssetGenerator::createTerrainMeshVao(unsigned int& vao, unsigned int vertexBufferId, unsigned int indexBufferId, unsigned int instanceBufferId) {
        Engine::Vao::generate(vao);
        Engine::Vao::bind(vao);
        Engine::VertexBuffer::bind(vertexBufferId);
        Engine::IndexBuffer::bind(indexBufferId);
        Engine::Vao::vertexAttributeIntegerPointer(0, 2, GL_UNSIGNED_BYTE, 2, 0);
        Engine::VertexBuffer::bind(instanceBufferId);
        Engine::Vao::vertexAttributeIntegerPointerInstanced(1, 2, GL_UNSIGNED_BYTE, 3, 0);
        Engine::Vao::vertexAttributeIntegerPointerInstanced(2, 1, GL_UNSIGNED_BYTE, 3, 2);
        Engine::Vao::unbind();
    }
}