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

/*        struct GalaxyData {
            glm::mat4 model;
            glm::vec4 color;
            GalaxyData(glm::mat4 model, glm::vec4 color) : model(model), color(color) {}
        };*/

        std::vector<Engine::ParticleSystem::ParticleData> galaxyData;

/*        for(int i = 0; i < MAX_GALAXIES; i++){
            glm::vec3 randomPos = Engine::Random::randomVec3(glm::vec3(-2.f, -2.f, -2.f), glm::vec3(2.f,2.f,2.f));
            glm::vec3 randomRot = Engine::Random::randomVec3(glm::vec3(90.f, 0.f, 0.f), glm::vec3(90.f, 0.f, 0.f));

            glm::mat4 model = glm::translate(glm::mat4(1), randomPos) * glm::eulerAngleXYZ(randomRot.x, randomRot.y, randomRot.z);
            glm::vec4 color = glm::vec4(Engine::Random::randomVec3(glm::vec3(0.8, 0.8, 0.8), glm::vec3(1, 1, 1)), 1);

            galaxyData.push_back(GalaxyData(model, color));
        }*/

        for(int i = 0; i < MAX_GALAXIES; i++){
            Engine::ParticleSystem::ParticleData pd;
            pd.position = glm::vec3(Engine::Random::randomFloat(-1.f, 1.f), Engine::Random::randomFloat(-1.f, 1.f), -i * 0.1f);//Engine::Random::randomVec3(glm::vec3(-5.f, -5.f, -5.f), glm::vec3(5.f,5.f,5.f));
            pd.rotation = Engine::Random::randomFloat(0.f, 360.f);
            pd.scale = Engine::Random::randomFloat(0.1f, 0.3f);
            pd.color = glm::vec4(Engine::Random::randomVec3(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f,1.f,1.f)), 1.f);
            galaxyData.push_back(pd);
        }

        Engine::Core* core = Engine::Core::getInstance();

        Engine::VertexBuffer::VertexBuffer* billboardMeshVertexBuffer = core->assetManager.loadBillboardMesh("billboard");

        Engine::VertexBuffer::generate(galaxyInstanceBuffer.bufferId);
        Engine::VertexBuffer::bufferData(galaxyInstanceBuffer.bufferId, MAX_GALAXIES * sizeof(Engine::ParticleSystem::ParticleData), &galaxyData[0]);

        Engine::Vao::createBillboardMeshVao(galaxyMeshVao.vao, billboardMeshVertexBuffer->bufferId, galaxyInstanceBuffer.bufferId);

        shaderProgram = *(core->assetManager.loadShaderProgram("shader/particle.vert", "shader/particle_textured.frag", "galaxy"));
        shaderProgram.bind();
        shaderProgram.uniform("particleTexture", 0);

        Engine::Texture::generateGalaxyFrameBufferTexture(texture2D.textureId, 256);//*(core->assetManager.loadTexture2D("texture/noise.jpg", 1, "noise"));
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

        glm::mat4 projection = glm::perspective(glm::radians(2.0f), core->eglContext.width_ / (float)core->eglContext.height_, 0.1f, 1000.0f);
        glm::vec3 cameraPosition(0,0,-200);
        glm::mat4 view = glm::lookAt(cameraPosition, glm::vec3(0), glm::vec3(0,1,0));

        shaderProgram.bind();
        shaderProgram.uniform("projection", projection);
        shaderProgram.uniform("view", view);
        glActiveTexture(GL_TEXTURE0 + 0);
        glBindTexture(GL_TEXTURE_2D, texture2D.textureId);

        Engine::DrawCommand::drawBillboardsInstanced(galaxyMeshVao.vao, MAX_GALAXIES);
    }

}