#include "pch.h"
#include "ParticleScene.h"

#include "DrawCommand.h"

#include <GLES3/gl32.h> // will be removed
#include "ext/matrix_clip_space.hpp"  // will be removed
#include "gtc/matrix_transform.hpp"   // will be removed

#define MAX_PARTICLES 8192

namespace Game{

    void ParticleScene::init(){

        unsigned int billboardMeshVertexBuffer;
        Engine::VertexBuffer::generateBillboardVertexBuffer(billboardMeshVertexBuffer);

        Engine::VertexBuffer::generate(particleInstanceBuffer, MAX_PARTICLES * sizeof(Engine::ParticleSystem::ParticleData), nullptr);

        Engine::Vao::createBillboardMeshVao(particleMeshVao, billboardMeshVertexBuffer, particleInstanceBuffer);

        particleSystem = new Engine::ParticleSystem::ParticleSystem;

        Engine::Shader::createShaderProgramParticle(shaderProgram);
    }

    void ParticleScene::update(float dt){

        particleSystem->update(dt);

        Engine::Core* core = Engine::Core::getInstance();

        glViewport(0, 0, core->eglContext.width_, core->eglContext.height_);
        glClearColor(0.15f, 0.15f, 0.15, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        targetHorizontalAngle += -core->input.pointerDelta.x * 0.01;
        horizontalAngle = glm::mix(horizontalAngle, targetHorizontalAngle, 0.1);
        float radius = 30;
        glm::vec3 cameraPosition(radius * glm::sin(horizontalAngle), 0, radius * glm::cos(horizontalAngle));
        glm::mat4 view = glm::lookAt(cameraPosition, glm::vec3(0), glm::vec3(0,1,0));
        glm::mat4 projection = glm::perspective(glm::radians(90.0f), core->eglContext.width_ / (float)core->eglContext.height_, 0.1f, 1000.0f);

        Engine::Shader::updateUniforms(shaderProgram, projection, view);
        Engine::VertexBuffer::bufferSubData(particleInstanceBuffer, 0, particleSystem->particleCount * sizeof(Engine::ParticleSystem::ParticleData), &particleSystem->particleData[0]);
        Engine::DrawCommand::drawBillboardsInstanced(particleMeshVao, particleSystem->particleCount);
    }

}