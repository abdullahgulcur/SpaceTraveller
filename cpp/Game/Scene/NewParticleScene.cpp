#include "pch.h"
#include "NewParticleScene.h"
#include "DrawCommand.h"
#include "FrameBuffer.h"

namespace Game {

    void NewParticleScene::init() {

        unsigned int billboardMeshVertexBuffer;
        Engine::VertexBuffer::generateBillboardVertexBuffer(billboardMeshVertexBuffer);
        Engine::VertexBuffer::generate(particleInstanceBuffer, 4096 * sizeof(Engine::ParticleSystem::ParticleGPUData), nullptr);
        Engine::Vao::createParticleMeshVao(particleMeshVao, billboardMeshVertexBuffer, particleInstanceBuffer);
        Engine::Shader::createShaderParticle(shaderProgram);

        unsigned int gridVertexBuffer;
        Engine::VertexBuffer::generateGridVertexBuffer(gridVertexBuffer, gridVertexCount);
        Engine::Vao::createGridVao(gridVao, gridVertexBuffer);
        Engine::Shader::createShaderGrid(shaderProgramGrid);

        cameraCtrl.SetTarget(glm::vec3(0.0f, 0.0f, 0.0f));
        cameraCtrl.SetDistance(15.0f);

        Engine::Camera::perspectiveProjection(camera.projection, 90.0f, Engine::Core::getInstance()->appSurface.getAspectRatio(), 0.1f, 1000.0f);

        Engine::ParticleSystem::start(particleSystem, Engine::Core::getInstance()->systemTimer.getTotalSeconds());

        glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    }

    void NewParticleScene::update(float dt) {

        Engine::Camera::perspectiveProjection(camera.projection, 90.0f, Engine::Core::getInstance()->appSurface.getAspectRatio(), 0.1f, 1000.0f);

        Engine::ParticleSystem::updateParticleSmoke(particleSystem, dt);

        Engine::FrameBuffer::refreshScreen();
        //cameraCtrl.update(camera, dt);

        Engine::Core* core = Engine::Core::getInstance();

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


        //Engine::Shader::updateUniforms(shaderProgram, camera.projection, camera.view);

        glm::mat4 projectionView = camera.projection * camera.view;
        glm::vec3 cameraRight;
        glm::vec3 cameraUp;
        Engine::Camera::getCameraRightAndUp(camera.view, cameraRight, cameraUp);
        Engine::Shader::updateUniforms(shaderProgram, projectionView, cameraRight, cameraUp);

        Engine::DrawCommand::drawQuadsInstanced(particleMeshVao, particleSystem.particleCount, particleInstanceBuffer, sizeof(Engine::ParticleSystem::ParticleGPUData), &particleSystem.gpuData[0]);

        Engine::Shader::updateUniforms(shaderProgramGrid, projectionView);
        Engine::DrawCommand::drawGrid(gridVao, gridVertexCount);

    }

}