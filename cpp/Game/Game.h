#pragma once

#include "Core.h"
#include "MeshData.h"
#include "Camera.h"

#include "UniverseScene.h"
#include "TerrainSceneTest.h"

#if PLATFORM == WIN
#include "PlanetSceneTest.h"
#endif

#include "SceneFrame.h"
#include "Universe.h"
#include "ShaderProgram.h"
#include "Gizmo.h"
#include "AssetGenerator.h"


#include "TerrainGeometryManager.h"

namespace Game {

    enum class SceneType {
        UNIVERSE = 0,
        TERRAIN_TEST = 1,
        PLANET_TEST = 2
    };

    class Game {
    private:

        static Game* instance;


        Engine::Gizmo::Grid grid;

    public:

        AssetGenerator assetGenerator;

        UniverseScene universeScene;
        TerrainSceneTest terrainSceneTest;
        SceneFrame sceneFrame;

#if PLATFORM == WIN
        PlanetSceneTest planetSceneTest;
#endif

        Engine::MeshData::MeshData sphereMeshData;
        Engine::Shader::PlanetShader planetShader;
        Engine::Shader::ShaderSun shaderSun;
        unsigned int perlinTextureId;
        unsigned int macroTextureId;
        unsigned int noiseTextureArrayId;
        unsigned int vaoSphereMesh;

        Universe universe;

        Engine::ParticleSystem::ParticleTunnel<1024> particleSystem;


        Engine::Camera::Camera camera;

        Engine::ParticleSystem::ParticleSolarSystem<256> particleSolarSystems;
        Engine::Shader::ShaderParticleSolarSystem shaderParticleSolarSystem;
        unsigned int vertexBufferBillboard;
        unsigned int vertexBufferQuad;
        unsigned int instanceBufferParticleDynamic;
        unsigned int vaoParticleSolarSystem;

        unsigned int instanceBufferTerrain;
        unsigned int vaoTerrainBlock;
        unsigned int vaoTerrainOuterDegenerate;
        Engine::MeshData::MeshData terrainBlockMeshData;
        Engine::MeshData::MeshData terrainOuterDegenerateMeshData;
        Engine::Shader::ShaderTerrain shaderTerrain;

        unsigned int quadVAO;

        SceneType sceneType;

        Engine::TerrainGeometryManager terrainGeometryManager;

        Game() {}
        ~Game() {}

        void init();
        void start();
        void update(float dt);

        static Game* getInstance();
    };
}