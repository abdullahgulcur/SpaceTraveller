#include "pch.h"
#include "Game.h"
#include "Vao.h"

namespace Game{

    Game* Game::instance;

    void Game::init(){

        sceneType = SceneType::TUNNEL_EFFECT;

        Engine::VertexBuffer::generateBillboardVertexBuffer(vertexBufferBillboard);
        Engine::VertexBuffer::generate(instanceBufferParticleDynamic, 4096, nullptr);

        Engine::Vao::createParticleMeshVao(vaoParticle, vertexBufferBillboard, instanceBufferParticleDynamic);
        Engine::Shader::createShaderParticle(shaderProgram);

        universe.init();

        universeScene.init();
        tunnelEffectScene.init();

        switch (sceneType) {
        case SceneType::UNIVERSE: {
            universeScene.start(); break;
        }
        case SceneType::TUNNEL_EFFECT: {
            tunnelEffectScene.start(); break;
        }
        case SceneType::SOLAR_SYSTEM: {
            
            break;
        }
        case SceneType::PLANET_ATMOSPHERE: {
            
            break;
        }
        case SceneType::PLANET_SURFACE: {
            
            break;
        }
        }


        Engine::Gizmo::init(grid);

    }

    void Game::update(float dt){

        switch (sceneType) {
        case SceneType::UNIVERSE: {
            universeScene.update(dt); break;
        }
        case SceneType::TUNNEL_EFFECT: {
            tunnelEffectScene.update(dt); break;
        }
        case SceneType::SOLAR_SYSTEM: {
            
            break;
        }
        case SceneType::PLANET_ATMOSPHERE: {
            
            break;
        }
        case SceneType::PLANET_SURFACE: {
            
            break;
        }
        }

        glm::mat4 projectionView = camera.projection * camera.view;
        
        Engine::Gizmo::update(grid, projectionView);

    }

    Game* Game::getInstance() {
        if (!instance)
            instance = new Game;
        return instance;
    }
}