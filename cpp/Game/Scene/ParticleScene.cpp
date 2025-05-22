#include "pch.h"
#include "ParticleScene.h"
#include "DrawCommand.h"
#include "FrameBuffer.h"

namespace Game{

    void ParticleScene::init(){

        unsigned int billboardMeshVertexBuffer;
        Engine::VertexBuffer::generateBillboardVertexBuffer(billboardMeshVertexBuffer);
        Engine::VertexBuffer::generate(particleInstanceBuffer, 8192 * sizeof(Engine::ParticleSystem::ParticleData), nullptr);
        Engine::Vao::createBillboardMeshVao(particleMeshVao, billboardMeshVertexBuffer, particleInstanceBuffer);
//        Engine::Shader::createShaderProgramParticle(shaderProgram);
        
        cameraCtrl.SetTarget(glm::vec3(0.0f, 0.0f, 0.0f));
        cameraCtrl.SetDistance(15.0f);

        Engine::Camera::perspectiveProjection(camera.projection, 90.0f, Engine::Core::getInstance()->appSurface.getAspectRatio(), 0.1f, 1000.0f);

        particleSystem = new Engine::ParticleSystem::ParticleSystem;
    }

    void ParticleScene::update(float dt){

        particleSystem->update(dt);
        Engine::FrameBuffer::refreshScreen();
        //cameraCtrl.update(camera, dt);

        Engine::Core* core = Engine::Core::getInstance();

        float deltaX = 0.f;
        float deltaY = 0.f;
        float scroll = 0.f;

#if PLATFORM == WIN

        if (core->input.getButtonDown(Engine::InputCode::Mouse_Left)) {
#endif
            //deltaX = core->input.getPointerDelta().x;
            //deltaY = -core->input.getPointerDelta().y;
            // set cursor invisible
#if PLATFORM == WIN
        }
#endif

        cameraCtrl.ProcessInput(deltaX * 0.01f, deltaY * 0.01f, 0.0f);
        cameraCtrl.Update(dt);

        Engine::Camera::view(camera.view, cameraCtrl.m_position, cameraCtrl.m_up);


        Engine::Shader::updateUniforms(shaderProgram, camera.projection, camera.view);
        Engine::DrawCommand::drawQuadsInstanced(particleMeshVao, particleSystem->particleCount, particleInstanceBuffer, sizeof(Engine::ParticleSystem::ParticleData), &particleSystem->particleData[0]);
    }

}