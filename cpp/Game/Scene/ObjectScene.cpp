#include "pch.h"
#include "ObjectScene.h"

#include "DrawCommand.h"
#include "FrameBuffer.h"

#include "gtc/matrix_transform.hpp"   // will be removed

namespace Game{

    void ObjectScene::init(){

        int radius = 7;
        for(int x = -radius; x <= radius; x++){
            for(int y = -radius; y <= radius; y++){
                for(int z = -radius; z <= radius; z++){
                    if(x == -radius || x == radius || y == -radius || y == radius || z == -radius || z == radius){
                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(x,y,z)) * glm::scale(model, glm::vec3(0.3)); // math class
                        models.push_back(model);
                    }
                }
            }
        }

        Engine::MeshData::loadStaticMeshTextured(meshData, "model/sphere.obj");
        Engine::VertexBuffer::generate(instanceBuffer, models.size() * sizeof(glm::mat4), &models[0]);
        Engine::Vao::createMeshVao(vao, meshData.vertexBuffer, meshData.indexBuffer.bufferId, instanceBuffer, true);
        Engine::Shader::createShaderProgramPhong(shaderProgram);
        Engine::Texture::createTexture2D(textureId, "texture/marble.jpg");

        cameraCtrl.init(camera);
    }

    void ObjectScene::update(float dt){

        cameraCtrl.update(camera, dt);
        Engine::FrameBuffer::refreshScreen();
        Engine::Shader::updateUniforms(shaderProgram, camera.projection, camera.view, textureId);
        Engine::DrawCommand::drawInstanced(vao, meshData.indexBuffer.totalIndices, meshData.indexBuffer.indexElementType, models.size());
    }

}