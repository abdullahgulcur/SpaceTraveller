#include "pch.h"
#include "core.h"

#include <GLES3/gl32.h> // will be removed
#include "glm.hpp"  // will be removed
#include "ext/matrix_clip_space.hpp"  // will be removed
#include "gtc/matrix_transform.hpp"   // will be removed

namespace Engine {

    Core* Core::instance;

    void Core::init(android_app *app_) {

        this->app_ = app_;
        app_->userData = this;

        eglContext.init(this->app_);
        input.init(app_);

        MeshData* meshData = assetManager.loadStaticMeshDataTextured("model/sphere.obj", "sphere");

        int radius = 7;
        for(int x = -radius; x <= radius; x++){
            for(int y = -radius; y <= radius; y++){
                for(int z = -radius; z <= radius; z++){
                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::translate(model, glm::vec3(x,y,z)) * glm::scale(model, glm::vec3(0.3));
                    models.push_back(model);
                }
            }
        }

        //------ create mesh renderer (instanced)
        VertexBuffer::generate(instanceBuffer.bufferId);
        VertexBuffer::bufferData(instanceBuffer.bufferId, models.size() * sizeof(glm::mat4), &models[0]);

        //------ create mesh renderer (non instanced)
        Vao::createMeshVao(vao.vao, meshData->vertexBuffer.bufferId, meshData->indexBuffer.bufferId, instanceBuffer.bufferId, true);
        //------

        ShaderProgram shaderProgram = *assetManager.loadShaderProgram("shader/phong.vert", "shader/phong.frag", "phong");
        shaderProgram.bind();
        shaderProgram.uniform("albedoTexture", 0);

        assetManager.loadCompressedTexture2D("texture/marble.astc", "marble");
        assetManager.loadTexture2D("texture/marble.jpg", "marble_");

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
    }

    void Core::update() {

        input.handleInput();

/*        if(y < -3)
            dir = 1;
        if(y > 3)
            dir = -1;

        y += dir * 0.1;*/



        eglContext.updateRenderArea();

        glViewport(0, 0, eglContext.width_, eglContext.height_);
        glClearColor(0.15f, 0.15f, 0.15, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(90.0f), eglContext.width_ / (float)eglContext.height_, 0.1f, 1000.0f);

        targetHorizontalAngle += -input.pointerDelta.x * 0.01;
        horizontalAngle = glm::mix(horizontalAngle, targetHorizontalAngle, 0.1);
        float radius = 30;
        glm::vec3 cameraPosition(radius * glm::sin(horizontalAngle), 0, radius * glm::cos(horizontalAngle));
        glm::mat4 view = glm::lookAt(cameraPosition, glm::vec3(0), glm::vec3(0,1,0));



        //glm::mat4 model = glm::mat4(1.0f);
        //model = glm::translate(model, glm::vec3(0,y,0)) * glm::scale(model, glm::vec3(1));

        MeshData meshData = assetManager.staticMeshDataCache["sphere"];
        ShaderProgram shaderProgram = assetManager.shaderProgramCache["phong"];
        Texture2D texture2D = assetManager.texture2DCache["marble_"];

        //------ update mesh renderer (instanced)
        shaderProgram.bind();
        shaderProgram.uniform("projection", projection);
        shaderProgram.uniform("view", view);
        //shaderProgram.uniform("model", model);
        glActiveTexture(GL_TEXTURE0 + 0);
        glBindTexture(GL_TEXTURE_2D, texture2D.textureId);

        Vao::bind(vao.vao);
        IndexBuffer::drawInstanced(meshData.indexBuffer.totalIndices, meshData.indexBuffer.indexElementType, models.size());
        //------

        eglContext.swapBuffers();
    }

    Core* Core::getInstance() {
        if (!instance)
            instance = new Core;
        return instance;
    }

}