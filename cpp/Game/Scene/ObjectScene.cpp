#include "pch.h"
#include "ObjectScene.h"

#include "DrawCommand.h"

#include <GLES3/gl32.h> // will be removed
#include "ext/matrix_clip_space.hpp"  // will be removed
#include "gtc/matrix_transform.hpp"   // will be removed

namespace Game{

    void ObjectScene::init(){

        int radius = 7;
        for(int x = -radius; x <= radius; x++){
            for(int y = -radius; y <= radius; y++){
                for(int z = -radius; z <= radius; z++){
                    if(x == -radius || x == radius || y == -radius || y == radius || z == -radius || z == radius){
                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(x,y,z)) * glm::scale(model, glm::vec3(0.3));
                        models.push_back(model);
                    }
                }
            }
        }

        Engine::MeshData::loadStaticMeshTextured(meshData, "model/sphere.obj");

        Engine::VertexBuffer::generate(instanceBuffer, models.size() * sizeof(glm::mat4), &models[0]);

        Engine::Vao::createMeshVao(vao, meshData.vertexBuffer, meshData.indexBuffer.bufferId, instanceBuffer, true);

        Engine::Shader::createShaderProgramPhong(shaderProgram);

        Engine::Texture::Texture2DConfig config;
        Engine::Texture::createTexture2D(textureId, config, "texture/marble.jpg");
    }

    void ObjectScene::update(float dt){

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

        Engine::Shader::updateUniforms(shaderProgram, projection, view, textureId);
        Engine::DrawCommand::drawInstanced(vao, meshData.indexBuffer.totalIndices, meshData.indexBuffer.indexElementType, models.size());
    }

}