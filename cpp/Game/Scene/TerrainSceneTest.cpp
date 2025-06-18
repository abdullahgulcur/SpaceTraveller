#include "pch.h"
#include "TerrainSceneTest.h"
#include "DrawCommand.h"
#include "FrameBuffer.h"
#include "Game.h"
#include "Vao.h"
#include "Core.h"

namespace Game{

    void TerrainSceneTest::init(){

    }

    void TerrainSceneTest::start() {

        cameraCtrl.init(Engine::Camera::CameraTransform(glm::vec3(0.f, 2.f, 0.f)));
    }

    void TerrainSceneTest::update(float dt){

        Engine::Core* core = Engine::Core::getInstance();
        Game* game = Game::getInstance();
        Engine::Input& input = core->input;
        Engine::Camera::Camera& camera = game->camera;

        if (input.getPointerDown()) {
            float deltaX = -input.getPointerDelta().x * 0.1f;
            float deltaY = input.getPointerDelta().y * 0.1f;
            cameraCtrl.addTargetPitch(deltaY);
            cameraCtrl.addTargetYaw(deltaX);
        }

        if (input.getButtonDown(Engine::InputCode::W))
            cameraCtrl.targetTransform.position = cameraCtrl.getPosition() + cameraCtrl.getForward();

        if (input.getButtonDown(Engine::InputCode::S))
            cameraCtrl.targetTransform.position = cameraCtrl.getPosition() - cameraCtrl.getForward();

        if (input.getButtonDown(Engine::InputCode::D))
            cameraCtrl.targetTransform.position = cameraCtrl.getPosition() + cameraCtrl.getRight();

        if (input.getButtonDown(Engine::InputCode::A))
            cameraCtrl.targetTransform.position = cameraCtrl.getPosition() - cameraCtrl.getRight();

        if (input.getButtonDown(Engine::InputCode::E))
            cameraCtrl.targetTransform.position = cameraCtrl.getPosition() + cameraCtrl.getUp();

        if (input.getButtonDown(Engine::InputCode::Q))
            cameraCtrl.targetTransform.position = cameraCtrl.getPosition() - cameraCtrl.getUp();

        cameraCtrl.update(dt);

        Engine::Camera::lookAt(camera, cameraCtrl.getPosition(), cameraCtrl.getPosition() + cameraCtrl.getForward(), glm::vec3(0.f, 1.f, 0.f));

        Engine::FrameBuffer::refreshScreen();

    }

}