#include "pch.h"
#include "TunnelEffectScene.h"
#include "DrawCommand.h"
#include "FrameBuffer.h"
#include "Game.h"
#include "ParticleSystem.h"

namespace Game{

    void TunnelEffectScene::init(){

    }

    void TunnelEffectScene::start() {

        Game* game = Game::getInstance();

        Engine::ParticleSystem::start(game->particleSystem, Engine::Core::getInstance()->systemTimer.getTotalSeconds());
    }

    void TunnelEffectScene::update(float dt){

        Game* game = Game::getInstance();
        Engine::Core* core = Engine::Core::getInstance();

        Engine::Camera::Camera& camera = game->camera;

        Engine::Camera::perspectiveProjection(camera.projection, 90.0f, core->appSurface.getAspectRatio(), 0.1f, 1000.0f);

        Engine::ParticleSystem::update(game->particleSystem, dt, 1.f);

        Engine::FrameBuffer::refreshScreen();

        glm::vec3 camPos(0.f, 0.f, -10.f);
        Engine::Camera::view(camera.view, camPos, glm::vec3(0.f, 1.f, 0.f));

        glm::mat4 projectionView = camera.projection * camera.view;
        glm::vec3 cameraRight;
        glm::vec3 cameraUp;
        Engine::Camera::getCameraRightAndUp(camera.view, cameraRight, cameraUp);

        Engine::Shader::updateUniforms(game->shaderProgram, projectionView, cameraRight, cameraUp);

        Engine::ParticleSystem::ParticleGPUData gpuData[256];
        //Engine::ParticleSystem::fillInstanceData(game->particleSystem, gpuData);

        Engine::DrawCommand::drawQuadsInstanced(game->vaoParticle, game->particleSystem.particleCount, game->instanceBufferParticleDynamic, sizeof(Engine::ParticleSystem::ParticleGPUData), &gpuData[0]);


    }

}