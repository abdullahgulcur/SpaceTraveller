#include "pch.h"
#include "TunnelEffectScene.h"
#include "DrawCommand.h"
#include "FrameBuffer.h"

namespace Game{

    void TunnelEffectScene::init(){

        unsigned int billboardMeshVertexBuffer;
        Engine::VertexBuffer::generateBillboardVertexBuffer(billboardMeshVertexBuffer);
        Engine::VertexBuffer::generate(particleInstanceBuffer, 1024 * sizeof(Engine::ParticleSystem::ParticleData), nullptr);
        Engine::Vao::createBillboardMeshVao_P_S(particleMeshVao, billboardMeshVertexBuffer, particleInstanceBuffer);
        //Engine::Shader::createShaderParticlePS(shaderProgram);
        cameraCtrl.init(camera);
        Engine::ParticleSystem::start(particleSystem, Engine::Core::getInstance()->systemTimer.getTotalSeconds());
    }

    void TunnelEffectScene::update(float dt){

        Engine::ParticleSystem::updateParticleTunnelEffect(particleSystem, dt);
        Engine::FrameBuffer::refreshScreen();
        cameraCtrl.update(camera, dt);
        Engine::Shader::updateUniforms(shaderProgram, camera.projection, camera.view);
        Engine::DrawCommand::drawQuadsInstanced(particleMeshVao, particleSystem.particleCount, particleInstanceBuffer, 16, &particleSystem.gpuData[0]);
    }

}