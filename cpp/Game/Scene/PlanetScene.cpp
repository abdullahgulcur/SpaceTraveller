#include "pch.h"
#include "PlanetScene.h"
#include "Game.h"

#include "stb_image_write.h"

namespace Game {

    void PlanetScene::init() {

    }

    void PlanetScene::start() {

        cameraCtrl.init(Engine::Camera::CameraTransform(glm::vec3(500.f, 100.f, 500.f), -89.f, 0.f));

        Game* game = Game::getInstance();
        Engine::Camera::Camera& camera = game->camera;
        terrainGeometryManager.init(camera.position);
    }

    void PlanetScene::update(float dt) {
        
        Game* game = Game::getInstance();
        Engine::Input& input = game->input;
        Engine::Camera::Camera& camera = game->camera;
        
        terrainGeometryManager.update(camera.position);

        if (input.getPointerDown()) {
            float deltaX = -input.getPointerDelta().x * 0.1f;
            float deltaY = input.getPointerDelta().y * 0.1f;
            cameraCtrl.addTargetPitch(deltaY);
            cameraCtrl.addTargetYaw(deltaX);
        }
        
#if PLATFORM == WIN
        if (input.getButtonDown(Engine::InputCode::W))
            cameraCtrl.targetTransform.position = cameraCtrl.getPosition() + cameraCtrl.getForward() * 30.f;
        
        if (input.getButtonDown(Engine::InputCode::S))
            cameraCtrl.targetTransform.position = cameraCtrl.getPosition() - cameraCtrl.getForward() * 30.f;
        
        if (input.getButtonDown(Engine::InputCode::D))
            cameraCtrl.targetTransform.position = cameraCtrl.getPosition() + cameraCtrl.getRight() * 30.f;
        
        if (input.getButtonDown(Engine::InputCode::A))
            cameraCtrl.targetTransform.position = cameraCtrl.getPosition() - cameraCtrl.getRight() * 30.f;
        
        if (input.getButtonDown(Engine::InputCode::E))
            cameraCtrl.targetTransform.position = cameraCtrl.getPosition() + cameraCtrl.getUp() * 30.f;
        
        if (input.getButtonDown(Engine::InputCode::Q))
            cameraCtrl.targetTransform.position = cameraCtrl.getPosition() - cameraCtrl.getUp() * 30.f;
#endif
        
        cameraCtrl.update(dt);
        Engine::Camera::lookAt(camera, cameraCtrl.getPosition(), cameraCtrl.getPosition() + cameraCtrl.getForward(), glm::vec3(0.f, 1.f, 0.f));
       
        Shader::ShaderDataTerrain shaderData(camera, terrainGeometryManager.getBlockSize(), game->assetGenerator.heightmapTextureId);
        //shaderData.setHeightmap(game->asyncTextureGenerator.heightmapTextureId);
        game->renderingContext.submit(terrainGeometryManager, shaderData);

        //std::cout << "Camera x: " << camera.position.x << " z: " << camera.position.z << std::endl;

    }

}