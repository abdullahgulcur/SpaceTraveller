#include "pch.h"
#include "Game.h"
#include "Vao.h"
#include "VertexBuffer.h"

namespace Game{

    Game* Game::instance;

    void Game::init(){

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        sceneType = SceneType::UNIVERSE;

        Engine::VertexBuffer::generateBillboardVertexBuffer(vertexBufferBillboard);

        Engine::VertexBuffer::generate(instanceBufferParticleDynamic, 16384, nullptr);

        Engine::Vao::createParticleMeshVao(vaoParticle, vertexBufferBillboard, instanceBufferParticleDynamic);
        Engine::Shader::createShaderParticle(shaderProgram);

        universe.init();
        Engine::Gizmo::init(grid);
        universeScene.init();

        switch (sceneType) {
        case SceneType::UNIVERSE: {
            universeScene.start(); break;
        }
        case SceneType::TUNNEL_EFFECT: {
            //tunnelEffectScene.start(); break;
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

        Engine::Core* core = Engine::Core::getInstance();
        Engine::Camera::init(camera, 90.0f, core->appSurface.getAspectRatio());
    }

    void Game::update(float dt){

        switch (sceneType) {
        case SceneType::UNIVERSE: {
            universeScene.update(dt); break;
        }
        case SceneType::TUNNEL_EFFECT: {
            //tunnelEffectScene.update(dt); break;
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

        Engine::Gizmo::update(grid, camera.projectionView);

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