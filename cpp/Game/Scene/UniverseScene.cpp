#include "pch.h"
#include "UniverseScene.h"
#include "DrawCommand.h"
#include "FrameBuffer.h"
#include "Game.h"
#include "Vao.h"
#include "Core.h"

namespace Game{

    void UniverseScene::init(){

    }

    void UniverseScene::start() {

        Game* game = Game::getInstance();
        Engine::Core* core = Engine::Core::getInstance();

        Engine::ParticleSystem::start(game->particleSolarSystems, Engine::Core::getInstance()->systemTimer.getTotalSeconds());
        
        stateMovement = StateMovement::IDLE;
    }

    void UniverseScene::update(float dt){

        switch (stateMovement) {
        case StateMovement::IDLE: {
            UniverseScene::stateIdle(dt); break;
        }
        case StateMovement::ACCELERATING: {
            UniverseScene::stateAccelerating(dt); break;
        }
        case StateMovement::MOVING: {
            UniverseScene::stateMoving(dt); break;
        }
        }

    }

    void UniverseScene::stateIdle(float dt) {


        Engine::Core* core = Engine::Core::getInstance();
        Game* game = Game::getInstance();

        Engine::ParticleSystem::update(game->particleSolarSystems, dt, 1.f);

        Engine::Camera::Camera& camera = game->camera;

        Engine::FrameBuffer::refreshScreen();

        float deltaX = 0.f;
        float deltaY = 0.f;
        float scroll = 0.f;

#if PLATFORM == WIN

        if (core->input.getButtonDown(Engine::InputCode::Mouse_Left)) {
#endif
            for (int i = 0; i < game->particleSolarSystems.particleCount; i++) {

                glm::vec4 particlePosition(game->particleSolarSystems.posX[i], game->particleSolarSystems.posY[i], game->particleSolarSystems.posZ[i], 1.f);

                glm::vec4 clipSpace = camera.projectionView * particlePosition;
                glm::vec3 ndc = glm::vec3(clipSpace) / clipSpace.w;

                glm::vec2 screenSpaceCoordsNormalized = glm::vec2(ndc);

                glm::u16vec2 screenSpaceCoords;
                core->appSurface.getScreenSpaceCoordinate(screenSpaceCoords, screenSpaceCoordsNormalized);
                if (glm::distance(glm::vec2(screenSpaceCoords), glm::vec2(core->input.getPointerPosition())) < 10.f) {

                    stateMovement = StateMovement::ACCELERATING;
                    accStartTime = static_cast<float>(core->systemTimer.getTotalSeconds());
                    Engine::ParticleSystem::start(game->particleSystem, Engine::Core::getInstance()->systemTimer.getTotalSeconds());
                    return;
                }
            }

            deltaX = core->input.getPointerDelta().x;
            deltaY = -core->input.getPointerDelta().y;
#if PLATFORM == WIN
        }
#endif

        cameraCtrl.ProcessInput(deltaX * 0.01f, deltaY * 0.01f, 0.0f);
        cameraCtrl.Update(dt);

        Engine::Camera::lookAt(camera, cameraCtrl.m_position, glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));

        Engine::Shader::updateUniforms(game->shaderProgram, camera.projectionView, camera.right, camera.up);

        //Engine::DrawCommand::drawQuadsInstanced(vaoBillboardSolarSystems, game->universe.solarSystemList.size());

        Engine::ParticleSystem::ParticleGPUData gpuData[1024];
        Engine::ParticleSystem::fillInstanceData(game->particleSolarSystems, gpuData);
        Engine::DrawCommand::drawQuadsInstanced(game->vaoParticle, game->particleSolarSystems.particleCount, game->instanceBufferParticleDynamic, sizeof(Engine::ParticleSystem::ParticleGPUData), &gpuData[0]);

    }

    void UniverseScene::stateAccelerating(float dt) {


        Game* game = Game::getInstance();
        Engine::Core* core = Engine::Core::getInstance();

        float duration = static_cast<float>(core->systemTimer.getTotalSeconds()) - accStartTime;
        if (duration > accPeriod) {
            stateMovement = StateMovement::MOVING;
            return;
        }

        Engine::Camera::Camera& camera = game->camera;

        Engine::ParticleSystem::update(game->particleSystem, dt, duration / accPeriod); // change alpha and speed according to the time !?
        Engine::ParticleSystem::update(game->particleSolarSystems, dt, 1.f - duration / accPeriod);

        Engine::FrameBuffer::refreshScreen();

        Engine::Camera::lookAt(camera, cameraCtrl.m_position, glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));

        Engine::Shader::updateUniforms(game->shaderProgram, camera.projectionView, camera.right, camera.up);

        Engine::ParticleSystem::ParticleGPUData gpuData[1024];
        Engine::ParticleSystem::fillInstanceData(game->particleSystem, gpuData, camera.inverseView);

        Engine::DrawCommand::drawQuadsInstanced(game->vaoParticle, game->particleSystem.particleCount, game->instanceBufferParticleDynamic, sizeof(Engine::ParticleSystem::ParticleGPUData), &gpuData[0]);

        Engine::ParticleSystem::fillInstanceData(game->particleSolarSystems, gpuData);
        Engine::DrawCommand::drawQuadsInstanced(game->vaoParticle, game->particleSolarSystems.particleCount, game->instanceBufferParticleDynamic, sizeof(Engine::ParticleSystem::ParticleGPUData), &gpuData[0]);

    }

    void UniverseScene::stateMoving(float dt) {


        Game* game = Game::getInstance();
        Engine::Core* core = Engine::Core::getInstance();

        Engine::Camera::Camera& camera = game->camera;

        Engine::ParticleSystem::update(game->particleSystem, dt, 1.f); // change alpha and speed according to the time !?
        //Engine::ParticleSystem::update(game->particleSolarSystems, dt, 1.f - duration / accPeriod);

        Engine::FrameBuffer::refreshScreen();

        Engine::Camera::lookAt(camera, cameraCtrl.m_position, glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));

        Engine::Shader::updateUniforms(game->shaderProgram, camera.projectionView, camera.right, camera.up);

        Engine::ParticleSystem::ParticleGPUData gpuData[1024];
        Engine::ParticleSystem::fillInstanceData(game->particleSystem, gpuData, camera.inverseView);

        Engine::DrawCommand::drawQuadsInstanced(game->vaoParticle, game->particleSystem.particleCount, game->instanceBufferParticleDynamic, sizeof(Engine::ParticleSystem::ParticleGPUData), &gpuData[0]);

        /*Engine::ParticleSystem::fillInstanceData(game->particleSolarSystems, gpuData);
        Engine::DrawCommand::drawQuadsInstanced(game->vaoParticle, game->particleSolarSystems.particleCount, game->instanceBufferParticleDynamic, sizeof(Engine::ParticleSystem::ParticleGPUData), &gpuData[0]);*/

    }

}