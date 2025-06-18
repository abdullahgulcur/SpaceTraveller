#pragma once

#include "Core.h"
#include "MeshData.h"
#include "Camera.h"

#include "UniverseScene.h"
#include "TerrainSceneTest.h"

#include "Universe.h"
#include "ShaderProgram.h"
#include "Gizmo.h"

namespace Game {

    enum class SceneType {
        UNIVERSE = 0,
        TERRAIN_TEST = 1
    };

    class Game {
    private:

        static Game* instance;

        UniverseScene universeScene;
        TerrainSceneTest terrainSceneTest;
        
        Engine::Gizmo::Grid grid;

    public:

        Engine::MeshData::MeshData sphereMeshData;
        Engine::Shader::PlanetShader planetShader;
        Engine::Shader::ShaderSun shaderSun;
        unsigned int perlinTextureId;
        unsigned int macroTextureId;
        unsigned int vaoSphereMesh;

        Universe universe;

        Engine::ParticleSystem::ParticleTunnel<1024> particleSystem;


        Engine::Camera::Camera camera;

        Engine::ParticleSystem::ParticleSolarSystem<256> particleSolarSystems;
        Engine::Shader::ShaderParticleSolarSystem shaderParticleSolarSystem;
        unsigned int vertexBufferBillboard;
        unsigned int instanceBufferParticleDynamic;
        unsigned int vaoParticleSolarSystem;

        unsigned int instanceBufferTerrain;
        unsigned int vaoTerrainBlock;
        unsigned int vaoTerrainOuterDegenerate;
        Engine::MeshData::MeshData terrainBlockMeshData;
        Engine::MeshData::MeshData terrainOuterDegenerateMeshData;
        Engine::Shader::ShaderTerrain shaderTerrain;

        SceneType sceneType;

        Game() {}
        ~Game() {}

        void init();
        void start();
        void update(float dt);

        static Game* getInstance();
    };
}