#include "pch.h"
#include "TunnelEffectScene.h"

#include "DrawCommand.h"

#include <GLES3/gl32.h> // will be removed
#include "ext/matrix_clip_space.hpp"  // will be removed
#include "gtc/matrix_transform.hpp"   // will be removed

namespace Game{

    void TunnelEffectScene::init(){

        Engine::Core* core = Engine::Core::getInstance();

        Engine::VertexBuffer::VertexBuffer* billboardMeshVertexBuffer = core->assetManager.loadBillboardMesh("billboard");

        Engine::VertexBuffer::generate(particleInstanceBuffer.bufferId);
        Engine::VertexBuffer::bufferData(particleInstanceBuffer.bufferId, 1024 * 16, nullptr);

        Engine::Vao::createBillboardMeshVao_P_S(particleMeshVao, billboardMeshVertexBuffer->bufferId, particleInstanceBuffer.bufferId);

        Engine::ParticleSystem::start(particleSystem, core->systemTimer.getTotalSeconds());

        shaderProgram = *(core->assetManager.loadShaderProgram("shader/particle_p_s.vert", "shader/particle.frag", "particle"));
    }

    void TunnelEffectScene::update(float dt){

        Engine::ParticleSystem::updateParticleTunnelEffect(particleSystem, dt);

        Engine::Core* core = Engine::Core::getInstance();

        glViewport(0, 0, core->eglContext.width_, core->eglContext.height_);
        glClearColor(0.15f, 0.15f, 0.15, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(90.0f), core->eglContext.width_ / (float)core->eglContext.height_, 0.1f, 1000.0f);

        targetHorizontalAngle += -core->input.pointerDelta.x * 0.01;
        horizontalAngle = glm::mix(horizontalAngle, targetHorizontalAngle, 0.1);
        float radius = 30;
        glm::vec3 cameraPosition(radius * glm::sin(horizontalAngle), 0, radius * glm::cos(horizontalAngle));
        glm::mat4 view = glm::lookAt(cameraPosition, glm::vec3(0), glm::vec3(0,1,0));

        shaderProgram.bind();
        shaderProgram.uniform("projection", projection);
        shaderProgram.uniform("view", view);

        Engine::VertexBuffer::bufferSubData(particleInstanceBuffer.bufferId, 0, particleSystem.particleCount * 16, &particleSystem.gpuData[0]);
        Engine::DrawCommand::drawBillboardsInstanced(particleMeshVao, particleSystem.particleCount);
    }

}