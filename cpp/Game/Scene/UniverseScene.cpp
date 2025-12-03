#include "pch.h"
#include "UniverseScene.h"
#include "DrawCommand.h"
#include "Shader.h"
#include "FrameBuffer.h"
#include "Game.h"
#include "Vao.h"
//#include "Core.h"

#include "gtx/rotate_vector.hpp"

#if PLATFORM == WIN

#ifdef IMGUI_ENABLE
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#endif // IMGUI_ENABLE

#endif

namespace Game {

    void UniverseScene::init() {}

    void UniverseScene::start() {

        Game* game = Game::getInstance();

        cameraCtrl.init(Engine::Camera::CameraTransform());

        glm::i16vec3 solarSystemPositions[256];
        for (int i = 0; i < game->sceneManager.universe.solarSystemList.size(); i++)
            solarSystemPositions[i] = game->sceneManager.universe.solarSystemList[i].position;

        ParticleSystem::start(game->assetGenerator.particleSolarSystems, solarSystemPositions);

        stateCameraMovement = StateCamera::UNIVERSE_IDLE;

#if PLATFORM == WIN

#ifdef IMGUI_ENABLE

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(game->appSurface.glfwContext.GLFW_window, true);
        ImGui_ImplOpenGL3_Init("#version 460");
#endif // IMGUI_ENABLE

#endif

    }

    void UniverseScene::update(float dt) {

        Game* game = Game::getInstance();

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

#if PLATFORM == WIN

#ifdef IMGUI_ENABLE
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Planet Properties");
        ImGui::Image(game->assetGenerator.sunFarBillboardTextureId, ImVec2(64, 64));

        ImGui::End();

        ImGui::Render();
#endif // IMGUI_ENABLE

#endif

        /* RENDER PART */
        //game->sceneFrame.activate();
        UniverseScene::submitStars();
        UniverseScene::submitSolarSystem();
        //game->sceneFrame.postProcess();

#if PLATFORM == WIN

#ifdef IMGUI_ENABLE
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif // IMGUI_ENABLE

#endif

    }

    void UniverseScene::stateUniverseIdle(float dt) {

        /* LOCALS */
        Game* game = Game::getInstance();
        Engine::Camera::Camera& camera = game->camera;
        ParticleSystem::ParticleSolarSystem<256>& particleSolarSystems = game->assetGenerator.particleSolarSystems;

        /* PARTICLE SYSTEM UPDATE */
        ParticleSystem::update(particleSolarSystems, 1.f);

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
        Game* game = Game::getInstance();
        Engine::Camera::Camera& camera = game->camera;
        ParticleSystem::ParticleSolarSystem<256>& particleSolarSystems = game->assetGenerator.particleSolarSystems;

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
        ParticleSystem::update(particleSolarSystems, 1.f);

        /* ENGINE CAMERA LOOK AT */
        Engine::Camera::lookAt(camera, translateCameraCtrl.getPosition(), translateCameraCtrl.getPosition() + translateCameraCtrl.getForward(), glm::vec3(0.f, 1.f, 0.f));
    }

    void UniverseScene::solarSystemIdle(float dt) {

        /* LOCALS */
        Game* game = Game::getInstance();
        Engine::Camera::Camera& camera = game->camera;
        ParticleSystem::ParticleSolarSystem<256>& particleSolarSystems = game->assetGenerator.particleSolarSystems;

        /* PARTICLE SYSTEM UPDATE */
        ParticleSystem::update(particleSolarSystems, 1.f);

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
        Game* game = Game::getInstance();
        Engine::Camera::Camera& camera = game->camera;
        ParticleSystem::ParticleSolarSystem<256>& particleSolarSystems = game->assetGenerator.particleSolarSystems;

        /* CAMERA UPDATE */
        translateCameraCtrl.update(dt);

        /* PARTICLE SYSTEM UPDATE */
        ParticleSystem::update(particleSolarSystems, 1.f);

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
        Game* game = Game::getInstance();
        Engine::Camera::Camera& camera = game->camera;
        ParticleSystem::ParticleSolarSystem<256>& particleSolarSystems = game->assetGenerator.particleSolarSystems;
        Engine::Input& input = game->input;

        /* PARTICLE SYSTEM UPDATE */
        ParticleSystem::update(particleSolarSystems, 1.f);

        /* CAMERA UPDATE */
        UniverseScene::translateCameraUpdate(dt);

        /* ENGINE CAMERA LOOK AT */
        Engine::Camera::lookAt(camera, cameraCtrl.getPosition(), cameraCtrl.getPosition() + cameraCtrl.getForward(), glm::vec3(0.f, 1.f, 0.f));

        if (UniverseScene::solarSystemClick())
            return;

        if (UniverseScene::planetClick())
            return;


        if (input.getPointerDown()) {
            glm::vec3 arrivalPoint = currentPlanet.relativePosition + glm::vec3(currentSun.position);
            UniverseScene::setCameraTransformQueue(arrivalPoint, arrivalPoint);
            translateCameraCtrl.init();
            stateCameraMovement = StateCamera::ORBIT_MOVE_TARGET;

            glm::vec2 position = glm::vec2(0.f);
            float rotation = 0.f;
            float scale = 1.f;
            float isBase = 0.f;
            game->renderingContext.terrainHeightmapGeneratorJobSystem.push(Shader::ShaderDataTerrainHeightmapGenerator(glm::vec2(0.f), 0.f, 1.f, 0.f));
            game->renderingContext.terrainHeightmapGeneratorJobSystem.set();

            return;
        }

//#if PLATFORM == WIN
//        if (input.getButtonPress(Engine::InputCode::Space)) { 
//            glm::vec3 arrivalPoint = currentPlanet.relativePosition + glm::vec3(currentSun.position);
//            UniverseScene::setCameraTransformQueue(arrivalPoint, arrivalPoint);
//            translateCameraCtrl.init();
//            stateCameraMovement = StateCamera::ORBIT_MOVE_TARGET;
//            return;
//        }
//#endif

    }

    void UniverseScene::stateOrbitMoveTarget(float dt) {

        /* LOCALS */
        Game* game = Game::getInstance();
        Engine::Camera::Camera& camera = game->camera;
        ParticleSystem::ParticleSolarSystem<256>& particleSolarSystems = game->assetGenerator.particleSolarSystems;
        
        /* PARTICLE SYSTEM UPDATE */
        ParticleSystem::update(particleSolarSystems, 1.f);

        /* CAMERA UPDATE */
        translateCameraCtrl.update(dt);

        /* ENGINE CAMERA LOOK AT */
        Engine::Camera::lookAt(camera, translateCameraCtrl.getPosition(), translateCameraCtrl.getPosition() + translateCameraCtrl.getForward(), glm::vec3(0.f, 1.f, 0.f));

        /* CAMERA UPDATE */
        if (glm::distance(translateCameraCtrl.getPosition(), currentPlanet.relativePosition + glm::vec3(currentSun.position)) < 3.1f) {
            game->sceneManager.sceneType = SceneType::PLANET;
            translateCameraCtrl.cleanQueue();
            game->sceneManager.planetScene.start();
            return;
        }
    }

    void UniverseScene::submitSolarSystem() {

        Game* game = Game::getInstance();
        Engine::Camera::Camera& camera = game->camera;

        //if (currentSun.id != -1) {
        //    glm::vec3 sunPosition = glm::vec3(currentSun.position);
        //    glm::mat4 model = glm::translate(glm::mat4(1), sunPosition) * glm::scale(glm::mat4(1), glm::vec3(6.f));

        //    Shader::ShaderDataSun shaderData;
        //    shaderData.projectionView = camera.projectionView;
        //    shaderData.model = model;
        //    Shader::updateUniforms(game->assetGenerator.shaderSun, shaderData);
        //    Engine::DrawCommand::draw(game->assetGenerator.vaoSphereMesh, game->assetGenerator.sphereMeshData.indexBuffer.totalIndices, game->assetGenerator.sphereMeshData.indexBuffer.indexElementType);
        //}

        //if (previousSun.id != -1) {
        //    glm::vec3 sunPosition = glm::vec3(previousSun.position);
        //    glm::mat4 model = glm::translate(glm::mat4(1), sunPosition) * glm::scale(glm::mat4(1), glm::vec3(6.f));

        //    Shader::ShaderDataSun shaderData;
        //    shaderData.projectionView = camera.projectionView;
        //    shaderData.model = model;
        //    Shader::updateUniforms(game->assetGenerator.shaderSun, shaderData);
        //    //Shader::updateUniforms(game->assetGenerator.shaderSun, camera.projectionView, model);
        //    Engine::DrawCommand::draw(game->assetGenerator.vaoSphereMesh, game->assetGenerator.sphereMeshData.indexBuffer.totalIndices, game->assetGenerator.sphereMeshData.indexBuffer.indexElementType);
        //}

        for (int i = 0; i < currentPlanetList.size(); i++) {

            Planet& planet = currentPlanetList[i];
            glm::vec3 position = glm::vec3(currentSun.position) + planet.relativePosition;
            glm::mat4 model = glm::translate(glm::mat4(1), position) * glm::scale(glm::mat4(1.f), glm::vec3(1.f));
            glm::vec3 lightDirection = glm::normalize(planet.relativePosition);
            Shader::ShaderDataPlanet planetShaderData(planet, camera, model, lightDirection, game->assetGenerator.noiseTextureArrayId);
            game->renderingContext.submit(planetShaderData);
        }

        for (int i = 0; i < previousPlanetList.size(); i++) {
            
            Planet& planet = previousPlanetList[i];
            glm::vec3 position = glm::vec3(previousSun.position) + planet.relativePosition;
            glm::mat4 model = glm::translate(glm::mat4(1), position) * glm::scale(glm::mat4(1.f), glm::vec3(1.f));
            glm::vec3 lightDirection = glm::normalize(planet.relativePosition);
            Shader::ShaderDataPlanet planetShaderData(planet, camera, model, lightDirection, game->assetGenerator.noiseTextureArrayId);
            game->renderingContext.submit(planetShaderData);
        }
    }

    void UniverseScene::submitStars() {

        Game* game = Game::getInstance();
        Shader::ShaderDataParticleSolarSystem shaderData(game->camera, game->appSurface.getAspectRatio(), game->assetGenerator.sunFarBillboardTextureId);
        game->renderingContext.submit(game->assetGenerator.particleSolarSystems, shaderData);
    }

    glm::vec3 UniverseScene::getArrivalPoint(glm::vec3& sunPosition) {

        float margin = 50.f;
        float verticalOffset = 20.f;
        glm::vec3 toSun = sunPosition - cameraCtrl.currentTransform.position;
        toSun.y = 0.f;
        float horizontalDistance = glm::length(toSun);
        glm::vec3 arrivalPoint = cameraCtrl.currentTransform.position + glm::normalize(toSun) * (horizontalDistance - margin);
        arrivalPoint.y = sunPosition.y + verticalOffset;
        return arrivalPoint;
    }

    glm::vec3 UniverseScene::getArrivalPointPlanet(glm::vec3& planetPosition, glm::vec3& sunPosition) {

        float margin = 3.f;
        //float verticalOffset = 5.f;
        glm::vec3 planetToSun = glm::normalize(sunPosition - planetPosition);
        glm::vec3 lateralOffset = glm::rotateY(planetToSun, glm::radians(90.f));
        glm::vec3 arrivalPoint = planetPosition + (planetToSun + lateralOffset + glm::vec3(0, 1, 0) * 0.5f) * margin;
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
        Game::getInstance()->appSurface.getScreenSpaceCoordinate(screenSpaceCoords, screenSpaceCoordsNormalized);
        return glm::vec2(screenSpaceCoords);
    }

    void UniverseScene::setPlanetList(unsigned int solarSystemId) {
        Game* game = Game::getInstance();

        previousSun = currentSun;
        currentSun = Sun(solarSystemId, game->sceneManager.universe.solarSystemList[solarSystemId].position);
        currentPlanet.id = -1;

        previousPlanetList.clean();

        for (int i = 0; i < currentPlanetList.size(); i++)
            previousPlanetList.push(currentPlanetList[i]);

        currentPlanetList.clean();
        for (int i = 0; i < game->sceneManager.universe.planetList.size(); i++) {
            Planet& planet = game->sceneManager.universe.planetList[i];
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

        Game* game = Game::getInstance();
        Engine::Camera::Camera& camera = game->camera;
        Engine::Input& input = game->input;

        if (input.getPointerClick()) {
            glm::vec2 pointerPosition = glm::vec2(input.getPointerPosition());

            for (int i = 0; i < game->sceneManager.universe.solarSystemList.size(); i++) {
                glm::vec3 sunPosition = glm::vec3(game->sceneManager.universe.solarSystemList[i].position);
                glm::vec2 screenSpaceSunPosition = UniverseScene::getPointScreenSpacePosition(camera.projectionView, sunPosition);

                if (glm::distance(screenSpaceSunPosition, pointerPosition) < 30.f) {
                    glm::vec3 arrivalPoint = UniverseScene::getArrivalPoint(sunPosition);
                    UniverseScene::setCameraTransformQueue(arrivalPoint, sunPosition);
                    translateCameraCtrl.init();
                    stateCameraMovement = StateCamera::UNIVERSE_MOVE_TARGET;
                    UniverseScene::setPlanetList(game->sceneManager.universe.solarSystemList[i].id);
                    return true;
                }
            }
        }
        return false;
    }

    bool UniverseScene::planetClick() {

        Game* game = Game::getInstance();
        Engine::Camera::Camera& camera = game->camera;
        Engine::Input& input = game->input;

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

        Engine::Input& input = Game::getInstance()->input;

        if (input.getPointerDown()) {
            float deltaX = -input.getPointerDelta().x * 0.1f;
            float deltaY = input.getPointerDelta().y * 0.1f;

            //std::cout << "X: " << deltaX << " Y: " << deltaY << std::endl;

            //__android_log_print(ANDROID_LOG_DEBUG, "MyAppTag", "x: %.2f y: %.2f", deltaX, deltaY);


            cameraCtrl.addTargetPitch(deltaY);
            cameraCtrl.addTargetYaw(deltaX);
        }
        cameraCtrl.update(dt);
    }


}