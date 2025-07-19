#pragma once

#include "MeshData.h"
#include "ShaderProgram.h"
#include "ParticleSystem.h"

namespace Game {

	class AssetGenerator {

	private:
	public:

        // ------- MESH -------
        Engine::MeshData::MeshData sphereMeshData;
        Engine::MeshData::MeshData terrainBlockMeshData;
        Engine::MeshData::MeshData terrainOuterDegenerateMeshData;

        // ------- sHADER -------
        Engine::Shader::PlanetShader planetShader;
        Engine::Shader::ShaderSun shaderSun;
        Engine::Shader::ShaderParticleSolarSystem shaderParticleSolarSystem;
        Engine::Shader::ShaderTerrain shaderTerrain;

        // ------- TEXTURE -------
        unsigned int perlinTextureId;
        unsigned int macroTextureId;
        unsigned int noiseTextureArrayId;
        unsigned int sunFarBillboardTextureId;

        // ------- VAO -------
        unsigned int vaoSphereMesh;
        unsigned int vaoParticleSolarSystem;
        unsigned int quadVAO;
        unsigned int vaoTerrainBlock;
        unsigned int vaoTerrainOuterDegenerate;

        // ------- PARTICLE -------
        Engine::ParticleSystem::ParticleTunnel<1024> particleSystem;
        Engine::ParticleSystem::ParticleSolarSystem<256> particleSolarSystems;

        // ------- VERTEX BUFFER -------
        unsigned int vertexBufferBillboard;
        unsigned int vertexBufferQuad;

        // ------- INSTANCE BUFFER -------
        unsigned int instanceBufferParticleDynamic;
        unsigned int instanceBufferTerrain;
        
		AssetGenerator() {}
		~AssetGenerator() {}

		void init();
		void generateSunBillboardTexture();
	};
}