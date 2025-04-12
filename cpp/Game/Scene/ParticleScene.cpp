#include "pch.h"
#include "ParticleScene.h"

#include "DrawCommand.h"

#include <GLES3/gl32.h> // will be removed
#include "ext/matrix_clip_space.hpp"  // will be removed
#include "gtc/matrix_transform.hpp"   // will be removed

#define MAX_PARTICLES 8192

namespace Game{

    void ParticleScene::init(){

        Engine::Core* core = Engine::Core::getInstance();

        Engine::VertexBuffer::VertexBuffer* billboardMeshVertexBuffer = core->assetManager.loadBillboardMesh("billboard");

        Engine::VertexBuffer::generate(particleInstanceBuffer.bufferId);
        Engine::VertexBuffer::bufferData(particleInstanceBuffer.bufferId, MAX_PARTICLES * sizeof(Engine::ParticleSystem::ParticleData), nullptr);

        Engine::Vao::createBillboardMeshVao(particleMeshVao.vao, billboardMeshVertexBuffer->bufferId, particleInstanceBuffer.bufferId);

        particleSystem = new Engine::ParticleSystem::ParticleSystem;
        shaderProgram = *(core->assetManager.loadShaderProgram("shader/particle.vert", "shader/particle.frag", "particle"));
        //shaderProgram.bind();
        //shaderProgram.uniform("albedoTexture", 0);

        /*core->assetManager.loadCompressedTexture2D("texture/marble.astc", "marble");
        core->assetManager.loadTexture2D("texture/marble.jpg", "marble_");*/
    }

    void ParticleScene::update(float dt){

        particleSystem->update(dt);

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
        //glActiveTexture(GL_TEXTURE0 + 0);
        //glBindTexture(GL_TEXTURE_2D, texture2D.textureId);

        Engine::VertexBuffer::bufferSubData(particleInstanceBuffer.bufferId, 0, particleSystem->particleCount * sizeof(Engine::ParticleSystem::ParticleData), &particleSystem->particleData[0]);
        Engine::DrawCommand::drawBillboardsInstanced(particleMeshVao.vao, particleSystem->particleCount);
    }

}