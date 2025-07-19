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


        Engine::VertexBuffer::generateBillboardVertexBuffer(vertexBufferBillboard);
        Engine::VertexBuffer::generateQuadVertexBuffer(vertexBufferQuad);

        Engine::VertexBuffer::generate(instanceBufferParticleDynamic, 16384, nullptr);
        Engine::VertexBuffer::generate(instanceBufferTerrain, 1224, nullptr); // level [0,10] her biri 4 byte, 36 + 27 * 9

        Engine::Vao::createParticleMeshSolarSystemVao(vaoParticleSolarSystem, vertexBufferBillboard, instanceBufferParticleDynamic);
        Engine::Vao::createQuadMeshVao(quadVAO, vertexBufferQuad);

        Engine::Shader::createShaderSun(shaderSun);
        Engine::Shader::createShaderParticleSolarSystem(shaderParticleSolarSystem);

        Engine::MeshData::generateQuadSphereMeshTextured(sphereMeshData);
        Engine::MeshData::generateTerrainBlockMesh(terrainBlockMeshData, 16);
        Engine::MeshData::generateTerrainOuterDegenerateMesh(terrainOuterDegenerateMeshData, 16);
        Engine::Vao::createTerrainMeshVao(vaoTerrainBlock, terrainBlockMeshData.vertexBuffer, terrainBlockMeshData.indexBuffer.bufferId, instanceBufferTerrain);
        Engine::Vao::createTerrainMeshVao(vaoTerrainOuterDegenerate, terrainOuterDegenerateMeshData.vertexBuffer, terrainOuterDegenerateMeshData.indexBuffer.bufferId, instanceBufferTerrain);

        Engine::Vao::createLitMeshTexturedVao(vaoSphereMesh, sphereMeshData.vertexBuffer, sphereMeshData.indexBuffer.bufferId);
        Engine::Shader::createShaderPlanet(planetShader);
        Engine::Texture::createTexture2D(perlinTextureId, "texture/noise/perlin.jpg");
        Engine::Texture::createTexture2D(macroTextureId, "texture/noise/macro.jpg");

        std::vector<std::string> pathList = {
            "texture/noise/perlin.jpg",
            "texture/noise/macro.jpg",
            "texture/noise/rock.jpg",
            "texture/noise/rocky.jpg",
            "texture/noise/soil.jpg",
            "texture/noise/stone.jpg",
            "texture/noise/grass.jpg"
        };
        Engine::Texture::createTextureArray2D(noiseTextureArrayId, pathList);

        Engine::Shader::createShaderTerrain(shaderTerrain);

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

        Engine::Shader::ShaderTextureGeneratorSun program;
        Engine::Shader::createShaderTextureGeneratorSun(program);

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
}