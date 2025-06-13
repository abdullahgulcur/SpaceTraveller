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

        glm::i16vec3 solarSystemPositions[256];
        for (int i = 0; i < game->universe.solarSystemList.size(); i++)
            solarSystemPositions[i] = game->universe.solarSystemList[i].position;
        
        Engine::ParticleSystem::start(game->particleSolarSystems, solarSystemPositions);
        
        stateCameraMovement = StateMaster::UNIVERSE_IDLE;
    }

    void UniverseScene::update(float dt){

        switch (stateCameraMovement) {
            case StateMaster::UNIVERSE_IDLE: {
                UniverseScene::stateUniverseIdle(dt); break;
            }
            case StateMaster::UNIVERSE_MOVE_TARGET: {
                UniverseScene::stateUniverseMoveTarget(dt); break;
            }
            case StateMaster::SOLAR_SYSTEM_IDLE: {
                UniverseScene::solarSystemIdle(dt); break;
            }
        }

    }

    void UniverseScene::stateUniverseIdle(float dt) {

        /* LOCALS */
        Engine::Core* core = Engine::Core::getInstance();
        Game* game = Game::getInstance();
        Engine::Camera::Camera& camera = game->camera;
        Engine::ParticleSystem::ParticleSolarSystem<256>& particleSolarSystems = game->particleSolarSystems;
        Engine::Input& input = core->input;
        Engine::AppSurface& appSurface = core->appSurface;

        /* PARTICLE SYSTEM UPDATE */
        Engine::ParticleSystem::update(particleSolarSystems, 1.f);

        /* CAMERA UPDATE */
        if (input.getPointerDown()) {
            float deltaX = -input.getPointerDelta().x * 0.1f;
            float deltaY = input.getPointerDelta().y * 0.1f;
            cameraCtrl.addTargetPitch(deltaY);
            cameraCtrl.addTargetYaw(deltaX);
        }
        cameraCtrl.update(dt);

        /* SOLAR SYSTEM CLICK */
        if (input.getPointerClick()) {
            glm::vec2 pointerPosition = glm::vec2(input.getPointerPosition());

            for (int i = 0; i < game->universe.solarSystemList.size(); i++) {
                glm::vec3 sunPosition = glm::vec3(game->universe.solarSystemList[i].position);
                glm::vec2 screenSpaceSunPosition = UniverseScene::getPointScreenSpacePosition(camera.projectionView, sunPosition);

                if (glm::distance(screenSpaceSunPosition, pointerPosition) < 10.f) {
                    glm::vec3 arrivalPoint = UniverseScene::getArrivalPoint(sunPosition);
                    UniverseScene::setCameraTransformQueue(arrivalPoint, sunPosition);
                    translateCameraCtrl.init();
                    stateCameraMovement = StateMaster::UNIVERSE_MOVE_TARGET;
                    currentSunIndex = i;
                    return;
                }
            }
        }

        /* ENGINE CAMERA LOOK AT */
        Engine::Camera::lookAt(camera, cameraCtrl.getPosition(), cameraCtrl.getPosition() + cameraCtrl.getForward(), glm::vec3(0.f, 1.f, 0.f));

        /* RENDER PART */
        Engine::FrameBuffer::refreshScreen();
        Engine::Shader::updateUniformsParticleFixedSize(game->shaderParticleSolarSystem, camera.projectionView, camera.right, camera.up, appSurface.getAspectRatio());
        Engine::ParticleSystem::ParticleGPUDataSolarSystem gpuData[256];
        Engine::ParticleSystem::fillInstanceData(particleSolarSystems, gpuData);
        Engine::DrawCommand::drawQuadsInstanced(game->vaoParticleSolarSystem, particleSolarSystems.particleCount, game->instanceBufferParticleDynamic, sizeof(Engine::ParticleSystem::ParticleGPUDataSolarSystem), &gpuData[0]);
    }

    void UniverseScene::stateUniverseMoveTarget(float dt) {

        /* LOCALS */
        Engine::Core* core = Engine::Core::getInstance();
        Game* game = Game::getInstance();
        Engine::Camera::Camera& camera = game->camera;
        Engine::ParticleSystem::ParticleSolarSystem<256>& particleSolarSystems = game->particleSolarSystems;
        Engine::Input& input = core->input;
        Engine::AppSurface& appSurface = core->appSurface;

        /* CAMERA UPDATE */
        if (!translateCameraCtrl.isUpdating) {
            stateCameraMovement = StateMaster::SOLAR_SYSTEM_IDLE;
            cameraCtrl.setTransform(translateCameraCtrl.transformQueue.back());
            translateCameraCtrl.cleanQueue();
            return;
        }
        translateCameraCtrl.update(dt);

        /* PARTICLE SYSTEM UPDATE */
        Engine::ParticleSystem::update(particleSolarSystems, 1.f);

        /* ENGINE CAMERA LOOK AT */
        Engine::Camera::lookAt(camera, translateCameraCtrl.getPosition(), translateCameraCtrl.getPosition() + translateCameraCtrl.getForward(), glm::vec3(0.f, 1.f, 0.f));


        /* RENDER PART */
        Engine::FrameBuffer::refreshScreen();
        Engine::Shader::updateUniformsParticleFixedSize(game->shaderParticleSolarSystem, camera.projectionView, camera.right, camera.up, appSurface.getAspectRatio());
        Engine::ParticleSystem::ParticleGPUDataSolarSystem gpuData[256];
        Engine::ParticleSystem::fillInstanceData(particleSolarSystems, gpuData);
        Engine::DrawCommand::drawQuadsInstanced(game->vaoParticleSolarSystem, particleSolarSystems.particleCount, game->instanceBufferParticleDynamic, sizeof(Engine::ParticleSystem::ParticleGPUDataSolarSystem), &gpuData[0]);

        glm::vec3 sunPosition = glm::vec3(game->universe.solarSystemList[currentSunIndex].position);
        glm::mat4 model = glm::translate(glm::mat4(1), sunPosition) * glm::scale(glm::mat4(1), glm::vec3(3.f));
        Engine::Shader::updateUniforms(game->shaderSun, camera.projectionView, model);
        Engine::DrawCommand::draw(game->vaoSphereMesh, game->sphereMeshData.indexBuffer.totalIndices, game->sphereMeshData.indexBuffer.indexElementType);
    }

    void UniverseScene::solarSystemIdle(float dt) {

        /* LOCALS */
        Engine::Core* core = Engine::Core::getInstance();
        Game* game = Game::getInstance();
        Engine::Camera::Camera& camera = game->camera;
        Engine::ParticleSystem::ParticleSolarSystem<256>& particleSolarSystems = game->particleSolarSystems;
        Engine::Input& input = core->input;
        Engine::AppSurface& appSurface = core->appSurface;

        /* PARTICLE SYSTEM UPDATE */
        Engine::ParticleSystem::update(particleSolarSystems, 1.f);

        /* CAMERA UPDATE */
        if (input.getPointerDown()) {
            float deltaX = -input.getPointerDelta().x * 0.1f;
            float deltaY = input.getPointerDelta().y * 0.1f;
            cameraCtrl.addTargetPitch(deltaY);
            cameraCtrl.addTargetYaw(deltaX);
        }
        cameraCtrl.update(dt);

        /* SOLAR SYSTEM CLICK */
        if (input.getPointerClick()) {
            glm::vec2 pointerPosition = glm::vec2(input.getPointerPosition());

            for (int i = 0; i < game->universe.solarSystemList.size(); i++) {
                glm::vec3 sunPosition = glm::vec3(game->universe.solarSystemList[i].position);
                glm::vec2 screenSpaceSunPosition = UniverseScene::getPointScreenSpacePosition(camera.projectionView, sunPosition);

                if (glm::distance(screenSpaceSunPosition, pointerPosition) < 10.f) {
                    glm::vec3 arrivalPoint = UniverseScene::getArrivalPoint(sunPosition);
                    UniverseScene::setCameraTransformQueue(arrivalPoint, sunPosition);
                    translateCameraCtrl.init();
                    stateCameraMovement = StateMaster::UNIVERSE_MOVE_TARGET;
                    currentSunIndex = i;
                    return;
                }
            }
        }

        /* ENGINE CAMERA LOOK AT */
        Engine::Camera::lookAt(camera, cameraCtrl.getPosition(), cameraCtrl.getPosition() + cameraCtrl.getForward(), glm::vec3(0.f, 1.f, 0.f));

        /* RENDER PART */
        Engine::FrameBuffer::refreshScreen();
        Engine::Shader::updateUniformsParticleFixedSize(game->shaderParticleSolarSystem, camera.projectionView, camera.right, camera.up, appSurface.getAspectRatio());
        Engine::ParticleSystem::ParticleGPUDataSolarSystem gpuData[256];
        Engine::ParticleSystem::fillInstanceData(particleSolarSystems, gpuData);
        Engine::DrawCommand::drawQuadsInstanced(game->vaoParticleSolarSystem, particleSolarSystems.particleCount, game->instanceBufferParticleDynamic, sizeof(Engine::ParticleSystem::ParticleGPUDataSolarSystem), &gpuData[0]);

        //glm::vec3 waterColor(0.1f, 0.3f, 0.9f);
        //glm::mat4 model = glm::translate(glm::mat4(1), glm::vec3(5.f, 0.f, 0.f) + camera.position);
        //Engine::Shader::updateUniforms(game->planetShader, camera.projectionView, model, camera.position,
        //    waterColor, 5.0f, 0.5f, 2.5f, 0.1f, 0.1f, game->perlinTextureId, game->macroTextureId);
        //Engine::DrawCommand::draw(game->vaoSphereMesh, game->sphereMeshData.indexBuffer.totalIndices, game->sphereMeshData.indexBuffer.indexElementType);

        glm::vec3 sunPosition = glm::vec3(game->universe.solarSystemList[currentSunIndex].position);
        glm::mat4 model = glm::translate(glm::mat4(1), sunPosition) * glm::scale(glm::mat4(1), glm::vec3(3.f));
        Engine::Shader::updateUniforms(game->shaderSun, camera.projectionView, model);
        Engine::DrawCommand::draw(game->vaoSphereMesh, game->sphereMeshData.indexBuffer.totalIndices, game->sphereMeshData.indexBuffer.indexElementType);
    }

    void UniverseScene::stateSolarSystemMoveTarget(float dt) {

    }

    glm::vec3 UniverseScene::getArrivalPoint(glm::vec3& sunPosition) {

        float margin = 15.f;
        float verticalOffset = 5.f;
        glm::vec3 toSun = sunPosition - cameraCtrl.currentTransform.position;
        toSun.y = 0.f;
        float horizontalDistance = glm::length(toSun);
        glm::vec3 arrivalPoint = cameraCtrl.currentTransform.position + glm::normalize(toSun) * (horizontalDistance - margin);
        arrivalPoint.y = sunPosition.y + verticalOffset;
        return arrivalPoint;
    }

    void UniverseScene::setCameraTransformQueue(glm::vec3& arrivalPoint, glm::vec3& lastLookAtPosition) {

        Engine::Camera::CameraTransform transform = cameraCtrl.currentTransform;
        translateCameraCtrl.push(transform, 0.f);
        Engine::Camera::computePitchYawFromTarget(transform.position, arrivalPoint, transform.pitch, transform.yaw);
        translateCameraCtrl.push(transform, 2.f);
        transform.position = arrivalPoint;
        translateCameraCtrl.push(transform, 4.f);
        Engine::Camera::computePitchYawFromTarget(arrivalPoint, lastLookAtPosition, transform.pitch, transform.yaw);
        translateCameraCtrl.push(transform, 6.f);
    }

    glm::vec2 UniverseScene::getPointScreenSpacePosition(glm::mat4& projectionView, glm::vec3& position) {

        glm::vec4 clipSpace = projectionView * glm::vec4(position, 1.f);
        glm::vec3 ndc = glm::vec3(clipSpace) / clipSpace.w;
        glm::vec2 screenSpaceCoordsNormalized = glm::vec2(ndc);
        glm::u16vec2 screenSpaceCoords;
        Engine::Core::getInstance()->appSurface.getScreenSpaceCoordinate(screenSpaceCoords, screenSpaceCoordsNormalized);
        return glm::vec2(screenSpaceCoords);
    }

}