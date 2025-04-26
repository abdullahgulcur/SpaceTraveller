#include "pch.h"
#include "UniverseScene.h"
#include "ParticleSystem.h"
#include "RandomValue.h"
#include "FrameBuffer.h"

#include "DrawCommand.h"

#include <GLES3/gl32.h> // will be removed
#include "ext/matrix_clip_space.hpp"  // will be removed
#include "gtc/matrix_transform.hpp"   // will be removed

#define GLM_ENABLE_EXPERIMENTAL
#include "gtx/euler_angles.hpp"

#define MAX_GALAXIES 256

namespace Game{

    void UniverseScene::init(){

        std::vector<Engine::ParticleSystem::ParticleData> galaxyData;

        for(int i = 0; i < MAX_GALAXIES; i++){
            Engine::ParticleSystem::ParticleData pd;
            pd.position = Engine::Random::randomVec3(glm::vec3(-10.f, -2.f, -30.f), glm::vec3(10.f,2.f,30.f));
            pd.rotation = Engine::Random::randomFloat(0.f, 360.f);
            pd.scale = Engine::Random::randomFloat(1.05f, 1.15f);
            pd.color = glm::vec4(1.f);// glm::vec4(Engine::Random::randomVec3(glm::vec3(1.0f, 0.6f, 0.6f), glm::vec3(1.f,0.5f,0.5f)), 1.f); // glm::vec4(1.f);//
            galaxyData.push_back(pd);
        }

        std::sort(galaxyData.begin(), galaxyData.end(), [](const Engine::ParticleSystem::ParticleData& a, const Engine::ParticleSystem::ParticleData& b) {
            return a.position.z > b.position.z;
        });

        unsigned int billboardMeshVertexBuffer;
        Engine::VertexBuffer::generateBillboardVertexBuffer(billboardMeshVertexBuffer);

        Engine::VertexBuffer::generate(galaxyInstanceBuffer, MAX_GALAXIES * sizeof(Engine::ParticleSystem::ParticleData), &galaxyData[0]);

        Engine::Vao::createBillboardMeshVao(galaxyMeshVao, billboardMeshVertexBuffer, galaxyInstanceBuffer);
        Engine::Shader::createShaderProgramParticleTextured(shaderProgram);
        Engine::Texture::generateGalaxyFrameBufferTexture(texture2D, 256);
    }

    void UniverseScene::update(float dt){

        Engine::Core* core = Engine::Core::getInstance();

        Engine::FrameBuffer::bindFbo(0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glViewport(0, 0, core->eglContext.width_, core->eglContext.height_);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        targetHorizontalPos += core->input.pointerDelta.x * 0.01;
        horizontalPos = glm::mix(horizontalPos, targetHorizontalPos, 0.1);

        glm::mat4 projection = glm::perspective(glm::radians(2.0f), core->eglContext.width_ / (float)core->eglContext.height_, 0.1f, 1000.0f);
        glm::vec3 cameraPosition(horizontalPos,0,-100);
        glm::mat4 view = glm::lookAt(cameraPosition, glm::vec3(horizontalPos,0,0), glm::vec3(0,1,0));

        Engine::Shader::updateUniforms(shaderProgram, projection, view, texture2D);

        Engine::DrawCommand::drawBillboardsInstanced(galaxyMeshVao, MAX_GALAXIES);
    }

}