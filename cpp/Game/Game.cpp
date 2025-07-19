#include "pch.h"
#include "Game.h"
#include "Vao.h"
#include "VertexBuffer.h"

namespace Game {

    Game* Game::instance;

    void Game::init() {


        assetGenerator.init();

        //sceneType = SceneType::TERRAIN_TEST;
        sceneType = SceneType::UNIVERSE;
        //sceneType = SceneType::PLANET_TEST;

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

        universe.init();
        Engine::Gizmo::init(grid);
        universeScene.init();
        terrainSceneTest.init();

        switch (sceneType) {
        case SceneType::UNIVERSE: {
            universeScene.start(); break;
        }
        case SceneType::TERRAIN_TEST: {
            terrainSceneTest.start(); break;
        }
        case SceneType::PLANET_TEST: {

#if PLATFORM == WIN
            planetSceneTest.start(); break;
#endif

        }
        }

        Engine::Core* core = Engine::Core::getInstance();
        Engine::Camera::init(camera, 45.0f, core->appSurface.getAspectRatio());

        glm::ivec2 screenSize;
        core->appSurface.getSize(screenSize);

        sceneFrame.init(screenSize);


        terrainGeometryManager.init(camera.position);
    }

    void Game::update(float dt) {

        terrainGeometryManager.update(camera.position);

        switch (sceneType) {
        case SceneType::UNIVERSE: {
            universeScene.update(dt); break;
        }
        case SceneType::TERRAIN_TEST: {
            terrainSceneTest.update(dt); break;
        }
        case SceneType::PLANET_TEST: {

#if PLATFORM == WIN
            planetSceneTest.update(dt); break;
#endif

        }
        }

        //Engine::Gizmo::update(grid, camera.projectionView);

        Engine::Core* core = Engine::Core::getInstance();
        if (core->appSurface.aspectChanged())
            Engine::Camera::setAspect(camera, core->appSurface.getAspectRatio());
    }

    Game* Game::getInstance() {
        if (!instance)
            instance = new Game;
        return instance;
    }
}