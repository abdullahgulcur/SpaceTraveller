#include "pch.h"
#include "NewParticleScene.h"
#include "DrawCommand.h"
#include "FrameBuffer.h"
#include "Vao.h"
#include "VertexBuffer.h"
#include "Game.h"

namespace Game {

    void NewParticleScene::init() {


        cameraCtrl.SetTarget(glm::vec3(0.0f, 0.0f, 0.0f));
        cameraCtrl.SetDistance(15.0f);

        Game* game = Game::getInstance();

        Engine::Camera::perspectiveProjection(game->camera.projection, 90.0f, Engine::Core::getInstance()->appSurface.getAspectRatio(), 0.1f, 1000.0f);

        Engine::ParticleSystem::start(particleSystem, Engine::Core::getInstance()->systemTimer.getTotalSeconds());

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    }

    void NewParticleScene::update(float dt) {

        Game* game = Game::getInstance();
        Engine::Core* core = Engine::Core::getInstance();

        Engine::Camera::Camera& camera = game->camera;

        Engine::Camera::perspectiveProjection(camera.projection, 90.0f, core->appSurface.getAspectRatio(), 0.1f, 1000.0f);

        Engine::ParticleSystem::updateParticle(particleSystem, dt);

        Engine::FrameBuffer::refreshScreen();
        //cameraCtrl.update(camera, dt);


        float deltaX = 0.f;
        float deltaY = 0.f;
        float scroll = 0.f;

#if PLATFORM == WIN

        if (core->input.getButtonDown(Engine::InputCode::Mouse_Left)) {
#endif
            deltaX = core->input.getPointerDelta().x;
            deltaY = -core->input.getPointerDelta().y;
            // set cursor invisible
#if PLATFORM == WIN
        }
#endif

        cameraCtrl.ProcessInput(deltaX * 0.01f, deltaY * 0.01f, 0.0f);
        cameraCtrl.Update(dt);

        Engine::Camera::view(camera.view, cameraCtrl.m_position, cameraCtrl.m_up);

        glm::mat4 projectionView = camera.projection * camera.view;
        glm::vec3 cameraRight;
        glm::vec3 cameraUp;
        Engine::Camera::getCameraRightAndUp(camera.view, cameraRight, cameraUp);


        //Engine::Entity::update(entityParticle, particleInstanceBuffer, projectionView, cameraRight, cameraUp, particleSystem);


        Engine::Shader::updateUniforms(game->shaderProgram, projectionView, cameraRight, cameraUp);

        Engine::ParticleSystem::ParticleGPUData gpuData[4096];
        Engine::ParticleSystem::fillInstanceData(particleSystem, gpuData);

        Engine::DrawCommand::drawQuadsInstanced(game->vaoParticle, particleSystem.particleCount, game->instanceBufferParticleDynamic, sizeof(Engine::ParticleSystem::ParticleGPUData), &gpuData[0]);


    }

}