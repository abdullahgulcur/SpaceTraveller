#pragma once
#include "Shader.h"
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

        // ------- SHADER -------
        Shader::ShaderPlanet planetShader;
        Shader::ShaderSun shaderSun;
        Shader::ShaderParticleSolarSystem shaderParticleSolarSystem;
        Shader::ShaderTerrain shaderTerrain;

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
        ParticleSystem::ParticleTunnel<1024> particleSystem;
        ParticleSystem::ParticleSolarSystem<256> particleSolarSystems;

        // ------- VERTEX BUFFER -------
        unsigned int vertexBufferBillboard;
        unsigned int vertexBufferQuad;

        // ------- INSTANCE BUFFER -------
        unsigned int instanceBufferParticleDynamic;
        unsigned int instanceBufferTerrain;
        
		AssetGenerator() {}
		~AssetGenerator() {}

        void init();
        void initRenderObjects();
		void generateSunBillboardTexture();

        // -------------- VAO --------------

        void createParticleMeshVao(unsigned int& vao, unsigned int vertexBufferId, unsigned int instanceBufferId);
        void createParticleMeshSolarSystemVao(unsigned int& vao, unsigned int vertexBufferId, unsigned int instanceBufferId);
        void createGalaxyMeshVao(unsigned int& vao, unsigned int vertexBufferId, unsigned int instanceBufferId);
        void createTerrainMeshVao(unsigned int& vao, unsigned int vertexBufferId, unsigned int indexBufferId, unsigned int instanceBufferId);
	};
}