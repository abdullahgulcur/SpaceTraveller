#include "pch.h"
#include "UniverseScene.h"
#include "DrawCommand.h"
#include "FrameBuffer.h"
#include "Game.h"
#include "Vao.h"
#include "Core.h"

namespace Game {

    void UniverseScene::init() {

    }

    void UniverseScene::start() {

        Game* game = Game::getInstance();
        Engine::Core* core = Engine::Core::getInstance();

        cameraCtrl.init(Engine::Camera::CameraTransform());

        glm::i16vec3 solarSystemPositions[256];
        for (int i = 0; i < game->universe.solarSystemList.size(); i++)
            solarSystemPositions[i] = game->universe.solarSystemList[i].position;

        Engine::ParticleSystem::start(game->particleSolarSystems, solarSystemPositions);

        stateCameraMovement = StateCamera::UNIVERSE_IDLE;
    }

    void UniverseScene::update(float dt) {

        switch (stateCameraMovement) {
        case StateCamera::UNIVERSE_IDLE: {
            UniverseScene::stateUniverseIdle(dt); break;
        }
        case StateCamera::UNIVERSE_MOVE_TARGET: {
            UniverseScene::stateUniverseMoveTarget(dt); break;
        }
        case StateCamera::SOLAR_SYSTEM_IDLE: {
            UniverseScene::solarSystemIdle(dt); break;
        }
        case StateCamera::SOLAR_SYSTEM_MOVE_TARGET: {
            UniverseScene::stateSolarSystemMoveTarget(dt); break;
        }
        case StateCamera::ORBIT_IDLE: {
            UniverseScene::stateOrbitIdle(dt); break;
        }
        case StateCamera::ORBIT_MOVE_TARGET: {
            UniverseScene::stateOrbitMoveTarget(dt); break;
        }
        }

        /* RENDER PART */
        Game* game = Game::getInstance();

        game->sceneFrame.activate();

        UniverseScene::renderStars();
        UniverseScene::renderSolarSystem();

        game->sceneFrame.postProcess();
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
        UniverseScene::translateCameraUpdate(dt);

        /* ENGINE CAMERA LOOK AT */
        Engine::Camera::lookAt(camera, cameraCtrl.getPosition(), cameraCtrl.getPosition() + cameraCtrl.getForward(), glm::vec3(0.f, 1.f, 0.f));

        /* SOLAR SYSTEM CLICK */
        if (UniverseScene::solarSystemClick())
            return;
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
            stateCameraMovement = StateCamera::SOLAR_SYSTEM_IDLE;
            cameraCtrl.setTransform(translateCameraCtrl.transformQueue.back());
            translateCameraCtrl.cleanQueue();
            UniverseScene::cleanPreviousSolarSystem();
            return;
        }
        translateCameraCtrl.update(dt);

        /* PARTICLE SYSTEM UPDATE */
        Engine::ParticleSystem::update(particleSolarSystems, 1.f);

        /* ENGINE CAMERA LOOK AT */
        Engine::Camera::lookAt(camera, translateCameraCtrl.getPosition(), translateCameraCtrl.getPosition() + translateCameraCtrl.getForward(), glm::vec3(0.f, 1.f, 0.f));
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
        UniverseScene::translateCameraUpdate(dt);

        /* ENGINE CAMERA LOOK AT */
        Engine::Camera::lookAt(camera, cameraCtrl.getPosition(), cameraCtrl.getPosition() + cameraCtrl.getForward(), glm::vec3(0.f, 1.f, 0.f));

        if (UniverseScene::solarSystemClick())
            return;

        if (UniverseScene::planetClick())
            return;
    }

    void UniverseScene::stateSolarSystemMoveTarget(float dt) {

        /* LOCALS */
        Engine::Core* core = Engine::Core::getInstance();
        Game* game = Game::getInstance();
        Engine::Camera::Camera& camera = game->camera;
        Engine::ParticleSystem::ParticleSolarSystem<256>& particleSolarSystems = game->particleSolarSystems;
        Engine::Input& input = core->input;
        Engine::AppSurface& appSurface = core->appSurface;

        /* CAMERA UPDATE */
        translateCameraCtrl.update(dt);

        /* PARTICLE SYSTEM UPDATE */
        Engine::ParticleSystem::update(particleSolarSystems, 1.f);

        /* ENGINE CAMERA LOOK AT */
        Engine::Camera::lookAt(camera, translateCameraCtrl.getPosition(), translateCameraCtrl.getPosition() + translateCameraCtrl.getForward(), glm::vec3(0.f, 1.f, 0.f));


        /* CAMERA UPDATE */
        if (!translateCameraCtrl.isUpdating) {
            stateCameraMovement = StateCamera::ORBIT_IDLE;
            cameraCtrl.setTransform(translateCameraCtrl.transformQueue.back());
            translateCameraCtrl.cleanQueue();
            return;
        }
    }

    void UniverseScene::stateOrbitIdle(float dt) {

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
        UniverseScene::translateCameraUpdate(dt);

        /* ENGINE CAMERA LOOK AT */
        Engine::Camera::lookAt(camera, cameraCtrl.getPosition(), cameraCtrl.getPosition() + cameraCtrl.getForward(), glm::vec3(0.f, 1.f, 0.f));

        if (UniverseScene::solarSystemClick())
            return;

        if (UniverseScene::planetClick())
            return;

#if PLATFORM == WIN
        if (input.getButtonPress(Engine::InputCode::Space)) { 
            glm::vec3 arrivalPoint = currentPlanet.relativePosition + glm::vec3(currentSun.position);
            UniverseScene::setCameraTransformQueue(arrivalPoint, arrivalPoint);
            translateCameraCtrl.init();
            stateCameraMovement = StateCamera::ORBIT_MOVE_TARGET;
            return;
        }
#endif

    }

    void UniverseScene::stateOrbitMoveTarget(float dt) {

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
        translateCameraCtrl.update(dt);

        /* ENGINE CAMERA LOOK AT */
        Engine::Camera::lookAt(camera, translateCameraCtrl.getPosition(), translateCameraCtrl.getPosition() + translateCameraCtrl.getForward(), glm::vec3(0.f, 1.f, 0.f));

        /* CAMERA UPDATE */
        if (glm::distance(translateCameraCtrl.getPosition(), currentPlanet.relativePosition + glm::vec3(currentSun.position)) < 3.1f) {
            game->sceneType = SceneType::TERRAIN_TEST;
            translateCameraCtrl.cleanQueue();
            game->terrainSceneTest.start();
            return;
        }
    }

    void UniverseScene::renderSolarSystem() {

        Engine::Core* core = Engine::Core::getInstance();
        Game* game = Game::getInstance();
        Engine::Camera::Camera& camera = game->camera;

        if (currentSun.id != -1) {
            glm::vec3 sunPosition = glm::vec3(currentSun.position);
            glm::mat4 model = glm::translate(glm::mat4(1), sunPosition) * glm::scale(glm::mat4(1), glm::vec3(10.f));
            Engine::Shader::updateUniforms(game->shaderSun, camera.projectionView, model);
            Engine::DrawCommand::draw(game->vaoSphereMesh, game->sphereMeshData.indexBuffer.totalIndices, game->sphereMeshData.indexBuffer.indexElementType);
        }

        if (previousSun.id != -1) {
            glm::vec3 sunPosition = glm::vec3(previousSun.position);
            glm::mat4 model = glm::translate(glm::mat4(1), sunPosition) * glm::scale(glm::mat4(1), glm::vec3(10.f));
            Engine::Shader::updateUniforms(game->shaderSun, camera.projectionView, model);
            Engine::DrawCommand::draw(game->vaoSphereMesh, game->sphereMeshData.indexBuffer.totalIndices, game->sphereMeshData.indexBuffer.indexElementType);
        }

        for (int i = 0; i < currentPlanetList.size(); i++) {

            Planet& planet = currentPlanetList[i];

            glm::vec3 position = glm::vec3(currentSun.position) + planet.relativePosition;
            glm::mat4 model = glm::translate(glm::mat4(1), position) * glm::scale(glm::mat4(1.f), glm::vec3(3.f));
            glm::vec3 lightDirection = glm::normalize(planet.relativePosition);

            Engine::Shader::PlanetShaderData planetShaderData;
            planetShaderData.cameraPosition = camera.position;
            planetShaderData.projectionView = camera.projectionView;
            planetShaderData.model = model;
            planetShaderData.waterColor = planet.waterColor;
            planetShaderData.amountWater = planet.amountWater;
            planetShaderData.continentalShelfColor = planet.continentalShelfColor;
            planetShaderData.waterContinentalShelf = planet.continentalShelf;
            planetShaderData.lightDirection = lightDirection;
            planetShaderData.landColor0 = planet.landColor0;
            planetShaderData.landColor1 = planet.landColor1;
            planetShaderData.landColorOverlay = planet.landColorOverlay;
            planetShaderData.landColorPower = planet.landColorPower;
            planetShaderData.surfaceTopologyScale = planet.surfaceTopologyScale;
            planetShaderData.landColorBlendScale = planet.landColorBlendScale;
            planetShaderData.tex0 = game->perlinTextureId;
            planetShaderData.tex1 = game->macroTextureId;
            planetShaderData.texArray = game->noiseTextureArrayId;

            planetShaderData.macroScale = planet.macroScale;
            planetShaderData.cloudScale = planet.cloudScale;
            planetShaderData.cloudPower = planet.cloudPower;
            planetShaderData.cloudOverlay = planet.cloudOverlay;
            planetShaderData.cloudOpacity = planet.cloudOpacity;
            planetShaderData.cloudColor = planet.cloudColor;
            planetShaderData.fresnelPowerClouds = planet.fresnelPowerClouds;
            planetShaderData.fresnelScaleClouds = planet.fresnelScaleClouds;
            planetShaderData.fresnelBiasClouds = planet.fresnelBiasClouds;
            planetShaderData.fresnelPowerAtmosphere = planet.fresnelPowerAtmosphere;
            planetShaderData.fresnelScaleAtmosphere = planet.fresnelScaleAtmosphere;
            planetShaderData.fresnelBiasAtmosphere = planet.fresnelBiasAtmosphere;

            planetShaderData.noiseOctaveTexIndex0 = float(planet.noiseOctaveTexIndex0);
            planetShaderData.noiseOctaveTexIndex1 = float(planet.noiseOctaveTexIndex1);
            planetShaderData.noiseOctaveTexIndex2 = float(planet.noiseOctaveTexIndex2);
            planetShaderData.specularStrength = planet.specularStrength;
            planetShaderData.specularPower = planet.specularPower;

            Engine::Shader::updateUniforms(game->planetShader, planetShaderData);

            Engine::DrawCommand::draw(game->vaoSphereMesh, game->sphereMeshData.indexBuffer.totalIndices, game->sphereMeshData.indexBuffer.indexElementType);
        }

        for (int i = 0; i < previousPlanetList.size(); i++) {
            /*glm::vec3 waterColor(0.1f, 0.3f, 0.9f);
            glm::vec3 position = glm::vec3(previousSun.position) + previousPlanetList[i].relativePosition;
            glm::mat4 model = glm::translate(glm::mat4(1), position) * glm::scale(glm::mat4(1.f), glm::vec3(3.f));
            glm::vec3 lightDirection = glm::normalize(previousPlanetList[i].relativePosition);*/
            //Engine::Shader::updateUniforms(game->planetShader, camera.projectionView, model, camera.position, waterColor, waterColor, lightDirection, 5.0f, 0.5f, 2.5f, 0.1f, 0.1f, game->perlinTextureId, game->macroTextureId);


            Planet& planet = previousPlanetList[i];

            glm::vec3 position = glm::vec3(previousSun.position) + planet.relativePosition;
            glm::mat4 model = glm::translate(glm::mat4(1), position) * glm::scale(glm::mat4(1.f), glm::vec3(3.f));
            glm::vec3 lightDirection = glm::normalize(planet.relativePosition);

            Engine::Shader::PlanetShaderData planetShaderData;
            planetShaderData.cameraPosition = camera.position;
            planetShaderData.projectionView = camera.projectionView;
            planetShaderData.model = model;
            planetShaderData.waterColor = planet.waterColor;
            planetShaderData.amountWater = planet.amountWater;
            planetShaderData.continentalShelfColor = planet.continentalShelfColor;
            planetShaderData.waterContinentalShelf = planet.continentalShelf;
            planetShaderData.lightDirection = lightDirection;
            planetShaderData.landColor0 = planet.landColor0;
            planetShaderData.landColor1 = planet.landColor1;
            planetShaderData.landColorOverlay = planet.landColorOverlay;
            planetShaderData.landColorPower = planet.landColorPower;
            planetShaderData.surfaceTopologyScale = planet.surfaceTopologyScale;
            planetShaderData.landColorBlendScale = planet.landColorBlendScale;
            planetShaderData.tex0 = game->perlinTextureId;
            planetShaderData.tex1 = game->macroTextureId;
            planetShaderData.texArray = game->noiseTextureArrayId;

            planetShaderData.macroScale = planet.macroScale;
            planetShaderData.cloudScale = planet.cloudScale;
            planetShaderData.cloudPower = planet.cloudPower;
            planetShaderData.cloudOverlay = planet.cloudOverlay;
            planetShaderData.cloudOpacity = planet.cloudOpacity;
            planetShaderData.cloudColor = planet.cloudColor;
            planetShaderData.fresnelPowerClouds = planet.fresnelPowerClouds;
            planetShaderData.fresnelScaleClouds = planet.fresnelScaleClouds;
            planetShaderData.fresnelBiasClouds = planet.fresnelBiasClouds;
            planetShaderData.fresnelPowerAtmosphere = planet.fresnelPowerAtmosphere;
            planetShaderData.fresnelScaleAtmosphere = planet.fresnelScaleAtmosphere;
            planetShaderData.fresnelBiasAtmosphere = planet.fresnelBiasAtmosphere;
            planetShaderData.specularStrength = planet.specularStrength;
            planetShaderData.specularPower = planet.specularPower;

            planetShaderData.noiseOctaveTexIndex0 = float(planet.noiseOctaveTexIndex0);
            planetShaderData.noiseOctaveTexIndex1 = float(planet.noiseOctaveTexIndex1);
            planetShaderData.noiseOctaveTexIndex2 = float(planet.noiseOctaveTexIndex2);

            Engine::Shader::updateUniforms(game->planetShader, planetShaderData);

            Engine::DrawCommand::draw(game->vaoSphereMesh, game->sphereMeshData.indexBuffer.totalIndices, game->sphereMeshData.indexBuffer.indexElementType);
        }
    }

    void UniverseScene::renderStars() {

        Engine::Core* core = Engine::Core::getInstance();
        Game* game = Game::getInstance();
        Engine::Camera::Camera& camera = game->camera;
        Engine::ParticleSystem::ParticleSolarSystem<256>& particleSolarSystems = game->particleSolarSystems;
        Engine::AppSurface& appSurface = core->appSurface;

        Engine::Shader::updateUniformsParticleFixedSize(game->shaderParticleSolarSystem, camera.projectionView, camera.right, camera.up, appSurface.getAspectRatio());
        Engine::ParticleSystem::ParticleGPUDataSolarSystem gpuData[256];
        Engine::ParticleSystem::fillInstanceData(particleSolarSystems, gpuData);
        Engine::DrawCommand::drawQuadsInstanced(game->vaoParticleSolarSystem, particleSolarSystems.particleCount, game->instanceBufferParticleDynamic, sizeof(Engine::ParticleSystem::ParticleGPUDataSolarSystem), &gpuData[0]);
    }

    glm::vec3 UniverseScene::getArrivalPoint(glm::vec3& sunPosition) {

        float margin = 100.f;
        float verticalOffset = 20.f;
        glm::vec3 toSun = sunPosition - cameraCtrl.currentTransform.position;
        toSun.y = 0.f;
        float horizontalDistance = glm::length(toSun);
        glm::vec3 arrivalPoint = cameraCtrl.currentTransform.position + glm::normalize(toSun) * (horizontalDistance - margin);
        arrivalPoint.y = sunPosition.y + verticalOffset;
        return arrivalPoint;
    }

    glm::vec3 UniverseScene::getArrivalPointPlanet(glm::vec3& planetPosition, glm::vec3& sunPosition) {

        float margin = 7.f;
        float verticalOffset = 5.f;
        glm::vec3 planetToSun = glm::normalize(sunPosition - planetPosition);
        glm::vec3 arrivalPoint = planetPosition + planetToSun * margin;
        return arrivalPoint;
    }

    void UniverseScene::setCameraTransformQueue(glm::vec3& arrivalPoint, glm::vec3& lastLookAtPosition) {

        Engine::Camera::CameraTransform transform = cameraCtrl.currentTransform;
        translateCameraCtrl.push(transform, 0.f);
        Engine::Camera::computePitchYawFromTarget(transform.position, arrivalPoint, transform.pitch, transform.yaw);
        translateCameraCtrl.push(transform, 1.f);
        transform.position = arrivalPoint;
        translateCameraCtrl.push(transform, 2.f);
        Engine::Camera::computePitchYawFromTarget(arrivalPoint, lastLookAtPosition, transform.pitch, transform.yaw);
        translateCameraCtrl.push(transform, 3.f);
    }

    glm::vec2 UniverseScene::getPointScreenSpacePosition(glm::mat4& projectionView, glm::vec3& position) {

        glm::vec4 clipSpace = projectionView * glm::vec4(position, 1.f);
        glm::vec3 ndc = glm::vec3(clipSpace) / clipSpace.w;
        glm::vec2 screenSpaceCoordsNormalized = glm::vec2(ndc);
        glm::ivec2 screenSpaceCoords;
        Engine::Core::getInstance()->appSurface.getScreenSpaceCoordinate(screenSpaceCoords, screenSpaceCoordsNormalized);
        return glm::vec2(screenSpaceCoords);
    }

    void UniverseScene::setPlanetList(unsigned int solarSystemId) {
        Game* game = Game::getInstance();

        previousSun = currentSun;
        currentSun = Sun(solarSystemId, game->universe.solarSystemList[solarSystemId].position);
        currentPlanet.id = -1;

        previousPlanetList.clean();

        for (int i = 0; i < currentPlanetList.size(); i++)
            previousPlanetList.push(currentPlanetList[i]);

        currentPlanetList.clean();
        for (int i = 0; i < game->universe.planetList.size(); i++) {
            Planet& planet = game->universe.planetList[i];
            if (planet.solarSystemId == solarSystemId) {
                currentPlanetList.push(planet);
            }
        }
    }

    void UniverseScene::cleanPreviousSolarSystem() {
        previousSun.id = -1;
        previousPlanetList.clean();
    }

    bool UniverseScene::solarSystemClick() {

        Engine::Core* core = Engine::Core::getInstance();
        Game* game = Game::getInstance();
        Engine::Camera::Camera& camera = game->camera;
        Engine::Input& input = core->input;

        if (input.getPointerClick()) {
            glm::vec2 pointerPosition = glm::vec2(input.getPointerPosition());

            for (int i = 0; i < game->universe.solarSystemList.size(); i++) {
                glm::vec3 sunPosition = glm::vec3(game->universe.solarSystemList[i].position);
                glm::vec2 screenSpaceSunPosition = UniverseScene::getPointScreenSpacePosition(camera.projectionView, sunPosition);

                if (glm::distance(screenSpaceSunPosition, pointerPosition) < 30.f) {
                    glm::vec3 arrivalPoint = UniverseScene::getArrivalPoint(sunPosition);
                    UniverseScene::setCameraTransformQueue(arrivalPoint, sunPosition);
                    translateCameraCtrl.init();
                    stateCameraMovement = StateCamera::UNIVERSE_MOVE_TARGET;
                    UniverseScene::setPlanetList(game->universe.solarSystemList[i].id);
                    return true;
                }
            }
        }
        return false;
    }

    bool UniverseScene::planetClick() {

        Engine::Core* core = Engine::Core::getInstance();
        Game* game = Game::getInstance();
        Engine::Camera::Camera& camera = game->camera;
        Engine::Input& input = core->input;

        if (input.getPointerClick()) {
            glm::vec2 pointerPosition = glm::vec2(input.getPointerPosition());

            for (int i = 0; i < currentPlanetList.size(); i++) {
                glm::vec3 planetPosition = glm::vec3(currentSun.position) + currentPlanetList[i].relativePosition;
                glm::vec2 screenSpacePlanetPosition = UniverseScene::getPointScreenSpacePosition(camera.projectionView, planetPosition);

                if (glm::distance(screenSpacePlanetPosition, pointerPosition) < 100.f) {
                    glm::vec3 curentSunPosition = glm::vec3(currentSun.position);
                    glm::vec3 arrivalPoint = UniverseScene::getArrivalPointPlanet(planetPosition, curentSunPosition);
                    UniverseScene::setCameraTransformQueue(arrivalPoint, planetPosition);
                    translateCameraCtrl.init();
                    stateCameraMovement = StateCamera::SOLAR_SYSTEM_MOVE_TARGET;
                    currentPlanet = currentPlanetList[i];
                    return true;
                }
            }
        }
        return false;
    }

    void UniverseScene::translateCameraUpdate(float dt) {

        Engine::Core* core = Engine::Core::getInstance();
        Engine::Input& input = core->input;

        if (input.getPointerDown()) {
            float deltaX = -input.getPointerDelta().x * 0.1f;
            float deltaY = input.getPointerDelta().y * 0.1f;
            cameraCtrl.addTargetPitch(deltaY);
            cameraCtrl.addTargetYaw(deltaX);
        }
        cameraCtrl.update(dt);
    }


}