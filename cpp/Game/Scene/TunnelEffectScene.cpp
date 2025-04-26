#include "pch.h"
#include "TunnelEffectScene.h"

#include "DrawCommand.h"
#include "FrameBuffer.h"

#include "ext/matrix_clip_space.hpp"  // will be removed
#include "gtc/matrix_transform.hpp"   // will be removed

namespace Game{

    void TunnelEffectScene::init(){

        Engine::Core* core = Engine::Core::getInstance();

        unsigned int billboardMeshVertexBuffer;
        Engine::VertexBuffer::generateBillboardVertexBuffer(billboardMeshVertexBuffer);

        Engine::VertexBuffer::generate(particleInstanceBuffer, 1024 * sizeof(Engine::ParticleSystem::ParticleData), nullptr);

        Engine::Vao::createBillboardMeshVao_P_S(particleMeshVao, billboardMeshVertexBuffer, particleInstanceBuffer);

        Engine::ParticleSystem::start(particleSystem, core->systemTimer.getTotalSeconds());

        Engine::Shader::createShaderParticlePS(shaderProgram);
    }

    void TunnelEffectScene::update(float dt){

        Engine::ParticleSystem::updateParticleTunnelEffect(particleSystem, dt);

        Engine::Core* core = Engine::Core::getInstance();

        Engine::FrameBuffer::refreshScreen();

        glm::mat4 projection = glm::perspective(glm::radians(90.0f), core->eglContext.width_ / (float)core->eglContext.height_, 0.1f, 1000.0f);

        targetHorizontalAngle += -core->input.pointerDelta.x * 0.01;
        horizontalAngle = glm::mix(horizontalAngle, targetHorizontalAngle, 0.1);
        float radius = 30;
        glm::vec3 cameraPosition(radius * glm::sin(horizontalAngle), 0, radius * glm::cos(horizontalAngle));
        glm::mat4 view = glm::lookAt(cameraPosition, glm::vec3(0), glm::vec3(0,1,0));

        Engine::Shader::updateUniforms(shaderProgram, projection, view);
        Engine::DrawCommand::drawQuadsInstanced(particleMeshVao, particleSystem.particleCount, particleInstanceBuffer, 16, &particleSystem.gpuData[0]);
    }

}