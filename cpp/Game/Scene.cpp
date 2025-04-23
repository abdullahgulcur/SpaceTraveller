#include "pch.h"
#include "Scene.h"

#include "DrawCommand.h"

#include <GLES3/gl32.h> // will be removed
#include "ext/matrix_clip_space.hpp"  // will be removed
#include "gtc/matrix_transform.hpp"   // will be removed

namespace Game{

    void Scene::init(){

        Engine::Core* core = Engine::Core::getInstance();
        Engine::MeshData* meshData = core->assetManager.loadStaticMeshDataTextured("model/sphere.obj", "sphere");

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

        //------ create mesh renderer (instanced)
        Engine::VertexBuffer::generate(instanceBuffer.bufferId);
        Engine::VertexBuffer::bufferData(instanceBuffer.bufferId, models.size() * sizeof(glm::mat4), &models[0]);

        //------ create mesh renderer (non instanced)
        Engine::Vao::createMeshVao(vao, meshData->vertexBuffer.bufferId, meshData->indexBuffer.bufferId, instanceBuffer.bufferId, true);
        //------

        Engine::ShaderProgram shaderProgram = *(core->assetManager.loadShaderProgram("shader/phong.vert", "shader/phong.frag", "phong"));
        shaderProgram.bind();
        shaderProgram.uniform("albedoTexture", 0);

        core->assetManager.loadCompressedTexture2D("texture/marble.astc", "marble");
        core->assetManager.loadTexture2D("texture/marble.jpg", 3, "marble_");
    }

    void Scene::update(){

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

        //glm::mat4 model = glm::mat4(1.0f);
        //model = glm::translate(model, glm::vec3(0,y,0)) * glm::scale(model, glm::vec3(1));

        Engine::MeshData meshData = core->assetManager.staticMeshDataCache["sphere"];
        Engine::ShaderProgram shaderProgram = core->assetManager.shaderProgramCache["phong"];
        Engine::Texture2D texture2D = core->assetManager.texture2DCache["marble_"];

        //------ update mesh renderer (instanced)
        shaderProgram.bind();
        shaderProgram.uniform("projection", projection);
        shaderProgram.uniform("view", view);
        //shaderProgram.uniform("model", model);
        glActiveTexture(GL_TEXTURE0 + 0);
        glBindTexture(GL_TEXTURE_2D, texture2D.textureId);

        Engine::Vao::bind(vao);
        Engine::DrawCommand::drawInstanced(meshData.indexBuffer.totalIndices, meshData.indexBuffer.indexElementType, models.size());
    }

}