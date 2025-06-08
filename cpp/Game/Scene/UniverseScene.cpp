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

        cameraCtrl.init(Engine::Camera::CameraTransform());

        Engine::ParticleSystem::start(game->particleSolarSystems, core->systemTimer.getTotalSeconds());
        
        stateCameraMovement = StateCameraMovement::IDLE;
    }

    void UniverseScene::update(float dt){

        switch (stateCameraMovement) {
            case StateCameraMovement::IDLE: {
                UniverseScene::stateUniverse(dt); break;
            }
            case StateCameraMovement::MOVE: {
                UniverseScene::stateAccelerating(dt); break;
            }
        }

        //UniverseScene::stateUniverse(dt);

        /*switch (stateMovement) {
        case StateMovement::UNIVERSE: {
            UniverseScene::stateUniverse(dt); break;
        }
        case StateMovement::ACCELERATING: {
            UniverseScene::stateAccelerating(dt); break;
        }
        case StateMovement::MOVING: {
            UniverseScene::stateMoving(dt); break;
        }
        case StateMovement::SLOWING: {
            UniverseScene::stateSlowing(dt); break;
        }
        case StateMovement::SOLAR_SYSTEM: {
            UniverseScene::stateSolarSystem(dt); break;
        }
        case StateMovement::CAMERA_ORIENT: {
            UniverseScene::cameraOrient(dt); break;
        }
        }*/

    }

    //void UniverseScene::render() {

    //    Engine::Shader::updateUniforms(game->shaderProgram, camera.projectionView, camera.right, camera.up);

    //    Engine::ParticleSystem::ParticleGPUData gpuData[1024];
    //    Engine::ParticleSystem::fillInstanceData(particleSolarSystems, gpuData);
    //    Engine::DrawCommand::drawQuadsInstanced(game->vaoParticle, particleSolarSystems.particleCount, game->instanceBufferParticleDynamic, sizeof(Engine::ParticleSystem::ParticleGPUData), &gpuData[0]);

    //}

    void UniverseScene::stateUniverse(float dt) {


        Engine::Core* core = Engine::Core::getInstance();
        Game* game = Game::getInstance();
        Engine::Camera::Camera& camera = game->camera;
        Engine::ParticleSystem::ParticleSolarSystems<128>& particleSolarSystems = game->particleSolarSystems;
        Engine::Input& input = core->input;
        Engine::AppSurface& appSurface = core->appSurface;
        Engine::Timer::SystemTimer& systemTimer = core->systemTimer;

        Engine::ParticleSystem::update(particleSolarSystems, dt, 1.f);



        float deltaX = 0.f;
        float deltaY = 0.f;

        if (input.getPointerDown()) {
            deltaX = -input.getPointerDelta().x * 0.1f;
            deltaY = input.getPointerDelta().y * 0.1f;
        }

        if (input.getPointerClick()) {
            for (int i = 0; i < particleSolarSystems.particleCount; i++) {

                glm::vec4 particlePosition(particleSolarSystems.posX[i], particleSolarSystems.posY[i], particleSolarSystems.posZ[i], 1.f);

                glm::vec4 clipSpace = camera.projectionView * particlePosition;
                glm::vec3 ndc = glm::vec3(clipSpace) / clipSpace.w;
                glm::vec2 screenSpaceCoordsNormalized = glm::vec2(ndc);

                glm::u16vec2 screenSpaceCoords;
                appSurface.getScreenSpaceCoordinate(screenSpaceCoords, screenSpaceCoordsNormalized);
                if (glm::distance(glm::vec2(screenSpaceCoords), glm::vec2(input.getPointerPosition())) < 10.f) {

                    Engine::Camera::CameraTransform cameraTransform0 = cameraCtrl.currentTransform;
                    Engine::Camera::CameraTransform cameraTransform1(cameraCtrl.currentTransform.position);

                    translateCameraCtrl.transformQueue.push(cameraTransform0);
                    Engine::Camera::computePitchYawFromTarget(cameraCtrl.currentTransform.position, glm::vec3(particlePosition), cameraTransform1.pitch, cameraTransform1.yaw);
                    translateCameraCtrl.transformQueue.push(cameraTransform1);

                    Engine::Camera::CameraTransform cameraTransform2((glm::vec3(particlePosition)), cameraTransform1.pitch, cameraTransform1.yaw);
                    translateCameraCtrl.transformQueue.push(cameraTransform2);

                    translateCameraCtrl.durationQueue.push(0.f);
                    translateCameraCtrl.durationQueue.push(2.f);
                    translateCameraCtrl.durationQueue.push(4.f);
                    translateCameraCtrl.init();
                    
                    stateCameraMovement = StateCameraMovement::MOVE;
                    return;
                }
            }
        }

        cameraCtrl.addTargetPitch(deltaY);
        cameraCtrl.addTargetYaw(deltaX);
        cameraCtrl.update(dt);

        Engine::Camera::lookAt(camera, cameraCtrl.getPosition(), cameraCtrl.getPosition() + cameraCtrl.getForward(), glm::vec3(0.f, 1.f, 0.f));

        Engine::ParticleSystem::ParticleGPUData gpuData[1024];
        Engine::ParticleSystem::fillInstanceData(particleSolarSystems, gpuData);

        Engine::Shader::updateUniforms(game->shaderProgram, camera.projectionView, camera.right, camera.up);

        Engine::FrameBuffer::refreshScreen();

        Engine::DrawCommand::drawQuadsInstanced(game->vaoParticle, particleSolarSystems.particleCount, game->instanceBufferParticleDynamic, sizeof(Engine::ParticleSystem::ParticleGPUData), &gpuData[0]);
    }

    void UniverseScene::stateAccelerating(float dt) {

        Engine::Core* core = Engine::Core::getInstance();
        Game* game = Game::getInstance();
        Engine::Camera::Camera& camera = game->camera;
        Engine::ParticleSystem::ParticleSolarSystems<128>& particleSolarSystems = game->particleSolarSystems;
        Engine::Input& input = core->input;
        Engine::AppSurface& appSurface = core->appSurface;
        Engine::Timer::SystemTimer& systemTimer = core->systemTimer;

        if (!translateCameraCtrl.isUpdating) {
            stateCameraMovement = StateCameraMovement::IDLE;
            Engine::Camera::CameraTransform& ct = translateCameraCtrl.transformQueue.back();
            cameraCtrl.currentTransform = ct;
            cameraCtrl.targetTransform = ct;
            translateCameraCtrl.transformQueue.clean();
            translateCameraCtrl.durationQueue.clean();
            return;
        }

        Engine::ParticleSystem::update(particleSolarSystems, dt, 1.f);
        translateCameraCtrl.update(dt);

        Engine::Camera::lookAt(camera, translateCameraCtrl.getPosition(), translateCameraCtrl.getPosition() + translateCameraCtrl.getForward(), glm::vec3(0.f, 1.f, 0.f));


        Engine::FrameBuffer::refreshScreen();


        Engine::Shader::updateUniforms(game->shaderProgram, camera.projectionView, camera.right, camera.up);

        Engine::ParticleSystem::ParticleGPUData gpuData[1024];
        Engine::ParticleSystem::fillInstanceData(particleSolarSystems, gpuData);
        Engine::DrawCommand::drawQuadsInstanced(game->vaoParticle, particleSolarSystems.particleCount, game->instanceBufferParticleDynamic, sizeof(Engine::ParticleSystem::ParticleGPUData), &gpuData[0]);


        //Game* game = Game::getInstance();
        //Engine::Core* core = Engine::Core::getInstance();

        //float duration = static_cast<float>(core->systemTimer.getTotalSeconds()) - stopwatchStartTime;
        //if (duration > accPeriod) {
        //    stopwatchStartTime = static_cast<float>(core->systemTimer.getTotalSeconds());
        //    stateMovement = StateMovement::MOVING;
        //    return;
        //}

        //Engine::Camera::Camera& camera = game->camera;

        //Engine::ParticleSystem::update(game->particleSystem, dt, duration / accPeriod); // change alpha and speed according to the time !?
        //Engine::ParticleSystem::update(particleSolarSystems, dt, 1.f - duration / accPeriod);

        //Engine::FrameBuffer::refreshScreen();

        //Engine::Camera::lookAt(camera, cameraCtrl.m_position, glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));

        //Engine::Shader::updateUniforms(game->shaderProgram, camera.projectionView, camera.right, camera.up);

        //Engine::ParticleSystem::ParticleGPUData gpuData[1024];
        //Engine::ParticleSystem::fillInstanceData(game->particleSystem, gpuData, camera.inverseView);

        //Engine::DrawCommand::drawQuadsInstanced(game->vaoParticle, game->particleSystem.particleCount, game->instanceBufferParticleDynamic, sizeof(Engine::ParticleSystem::ParticleGPUData), &gpuData[0]);

        //Engine::ParticleSystem::fillInstanceData(particleSolarSystems, gpuData);
        //Engine::DrawCommand::drawQuadsInstanced(game->vaoParticle, particleSolarSystems.particleCount, game->instanceBufferParticleDynamic, sizeof(Engine::ParticleSystem::ParticleGPUData), &gpuData[0]);

    }

    void UniverseScene::stateMoving(float dt) {


        //Game* game = Game::getInstance();
        //Engine::Core* core = Engine::Core::getInstance();

        //float duration = static_cast<float>(core->systemTimer.getTotalSeconds()) - stopwatchStartTime;
        //if (duration > movePeriod) {
        //    stopwatchStartTime = static_cast<float>(core->systemTimer.getTotalSeconds());
        //    stateMovement = StateMovement::SLOWING;
        //    return;
        //}

        //Engine::Camera::Camera& camera = game->camera;

        //Engine::ParticleSystem::update(game->particleSystem, dt, 1.f);

        //Engine::FrameBuffer::refreshScreen();

        //Engine::Camera::lookAt(camera, cameraCtrl.m_position, glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));

        //Engine::Shader::updateUniforms(game->shaderProgram, camera.projectionView, camera.right, camera.up);

        //Engine::ParticleSystem::ParticleGPUData gpuData[1024];
        //Engine::ParticleSystem::fillInstanceData(game->particleSystem, gpuData, camera.inverseView);

        //Engine::DrawCommand::drawQuadsInstanced(game->vaoParticle, game->particleSystem.particleCount, game->instanceBufferParticleDynamic, sizeof(Engine::ParticleSystem::ParticleGPUData), &gpuData[0]);




        /*Engine::ParticleSystem::fillInstanceData(particleSolarSystems, gpuData);
        Engine::DrawCommand::drawQuadsInstanced(game->vaoParticle, particleSolarSystems.particleCount, game->instanceBufferParticleDynamic, sizeof(Engine::ParticleSystem::ParticleGPUData), &gpuData[0]);*/

    }

    void UniverseScene::stateSlowing(float dt) {


        //Game* game = Game::getInstance();
        //Engine::Core* core = Engine::Core::getInstance();

        //float duration = static_cast<float>(core->systemTimer.getTotalSeconds()) - stopwatchStartTime;
        //if (duration > accPeriod) {
        //    stateMovement = StateMovement::UNIVERSE;
        //    return;
        //}

        //Engine::Camera::Camera& camera = game->camera;

        //Engine::ParticleSystem::update(game->particleSystem, dt, 1.f - duration / accPeriod);
        //Engine::ParticleSystem::update(particleSolarSystems, dt, duration / accPeriod);

        //Engine::FrameBuffer::refreshScreen();

        //Engine::Camera::lookAt(camera, cameraCtrl.m_position, glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));

        //Engine::Shader::updateUniforms(game->shaderProgram, camera.projectionView, camera.right, camera.up);

        //Engine::ParticleSystem::ParticleGPUData gpuData[1024];
        //Engine::ParticleSystem::fillInstanceData(game->particleSystem, gpuData, camera.inverseView);

        //Engine::DrawCommand::drawQuadsInstanced(game->vaoParticle, game->particleSystem.particleCount, game->instanceBufferParticleDynamic, sizeof(Engine::ParticleSystem::ParticleGPUData), &gpuData[0]);

        //Engine::ParticleSystem::fillInstanceData(particleSolarSystems, gpuData);
        //Engine::DrawCommand::drawQuadsInstanced(game->vaoParticle, particleSolarSystems.particleCount, game->instanceBufferParticleDynamic, sizeof(Engine::ParticleSystem::ParticleGPUData), &gpuData[0]);

    }

    void UniverseScene::stateSolarSystem(float dt) {

        //Game* game = Game::getInstance();
        //Engine::Core* core = Engine::Core::getInstance();

        ////float duration = static_cast<float>(core->systemTimer.getTotalSeconds()) - stopwatchStartTime;
        ////if (duration > accPeriod) {
        ////    stateMovement = StateMovement::SOLAR_SYSTEM;
        ////    return;
        ////}

        //Engine::Camera::Camera& camera = game->camera;

        //Engine::ParticleSystem::update(game->particleSystem, dt, 1.f);
        ////Engine::ParticleSystem::update(particleSolarSystems, dt, duration / accPeriod);

        //Engine::FrameBuffer::refreshScreen();

        //Engine::Camera::lookAt(camera, cameraCtrl.m_position, glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));

        //Engine::Shader::updateUniforms(game->shaderProgram, camera.projectionView, camera.right, camera.up);

        //Engine::ParticleSystem::ParticleGPUData gpuData[1024];
        ///*Engine::ParticleSystem::fillInstanceData(game->particleSystem, gpuData, camera.inverseView);

        //Engine::DrawCommand::drawQuadsInstanced(game->vaoParticle, game->particleSystem.particleCount, game->instanceBufferParticleDynamic, sizeof(Engine::ParticleSystem::ParticleGPUData), &gpuData[0]);*/

        //Engine::ParticleSystem::fillInstanceData(particleSolarSystems, gpuData);
        //Engine::DrawCommand::drawQuadsInstanced(game->vaoParticle, particleSolarSystems.particleCount, game->instanceBufferParticleDynamic, sizeof(Engine::ParticleSystem::ParticleGPUData), &gpuData[0]);


    }

    //stateMovement = StateMovement::ACCELERATING;
    //stopwatchStartTime = static_cast<float>(core->systemTimer.getTotalSeconds());
    //Engine::ParticleSystem::start(game->particleSystem, Engine::Core::getInstance()->systemTimer.getTotalSeconds());
    //return;

    void UniverseScene::cameraOrient(float dt) {

        //Engine::Core* core = Engine::Core::getInstance();
        //Game* game = Game::getInstance();

        //float duration = static_cast<float>(core->systemTimer.getTotalSeconds()) - stopwatchStartTime;
        //if (duration > cameraOrientPeriod) {
        //    stopwatchStartTime = static_cast<float>(core->systemTimer.getTotalSeconds());
        //    stateMovement = StateMovement::ACCELERATING;
        //    Engine::ParticleSystem::start(game->particleSystem, Engine::Core::getInstance()->systemTimer.getTotalSeconds());
        //    return;
        //}

        //float alpha = duration / cameraOrientPeriod;

        //Engine::ParticleSystem::update(particleSolarSystems, dt, 1.f);

        //Engine::Camera::Camera& camera = game->camera;

        //Engine::FrameBuffer::refreshScreen();

        //Engine::Camera::lookAt(camera, cameraCtrl.m_position, glm::vec3(alpha), glm::vec3(0.f, 1.f, 0.f));

        //Engine::Shader::updateUniforms(game->shaderProgram, camera.projectionView, camera.right, camera.up);

        //Engine::ParticleSystem::ParticleGPUData gpuData[1024];
        //Engine::ParticleSystem::fillInstanceData(particleSolarSystems, gpuData);
        //Engine::DrawCommand::drawQuadsInstanced(game->vaoParticle, particleSolarSystems.particleCount, game->instanceBufferParticleDynamic, sizeof(Engine::ParticleSystem::ParticleGPUData), &gpuData[0]);

    }

    //void UniverseScene::startStopWatch() {

    //    stopwatchStartTime = static_cast<float>(Engine::Core::getInstance()->systemTimer.getTotalSeconds());
    //}

    //float UniverseScene::getDuration() {
    //    return static_cast<float>(Engine::Core::getInstance()->systemTimer.getTotalSeconds()) - stopwatchStartTime;
    //}


}