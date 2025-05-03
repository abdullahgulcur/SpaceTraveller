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
        Engine::Shader::createShaderProgramParticle(shaderProgram);
        cameraCtrl.init(camera);

        particleSystem = new Engine::ParticleSystem::ParticleSystem;
    }

    void ParticleScene::update(float dt){

        particleSystem->update(dt);
        Engine::FrameBuffer::refreshScreen();
        cameraCtrl.update(camera, dt);
        Engine::Shader::updateUniforms(shaderProgram, camera.projection, camera.view);
        Engine::DrawCommand::drawQuadsInstanced(particleMeshVao, particleSystem->particleCount, particleInstanceBuffer, sizeof(Engine::ParticleSystem::ParticleData), &particleSystem->particleData[0]);
    }

}