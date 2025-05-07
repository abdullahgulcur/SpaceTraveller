#include "pch.h"
#include "PlanetScene.h"

#include "DrawCommand.h"
#include "FrameBuffer.h"
#include "Vao.h"
#include "Texture2D.h"
#include "Core.h"
#include "ShaderProgram.h"
namespace Game{

    void PlanetScene::init(){

        model = glm::mat4(1);

        Engine::MeshData::generateQuadSphereVertexBuffer(meshData);
        Engine::Vao::createLitMeshVao(vao, meshData.vertexBuffer, meshData.indexBuffer.bufferId);
        Engine::Shader::createShaderPlanet(shader);
        Engine::Texture::createTexture2D(textureId0, "texture/noise/perlinnoise.jpg");
        Engine::Texture::createTexture2D(textureId1, "texture/noise/macrovariation.jpg");

        cameraCtrl.SetTarget(glm::vec3(0.0f, 0.0f, 0.0f));
        cameraCtrl.SetDistance(3.0f);

        Engine::Camera::perspectiveProjection(camera.projection, 90.0f, Engine::Core::getInstance()->appSurface.getAspectRatio(), 0.1f, 1000.0f);

    }

    void PlanetScene::update(float dt){

        Engine::Core* core = Engine::Core::getInstance();

        Engine::Camera::perspectiveProjection(camera.projection, 90.0f, Engine::Core::getInstance()->appSurface.getAspectRatio(), 0.1f, 1000.0f);
        
        float deltaX = 0.f;
        float deltaY = 0.f;
        float scroll = 0.f;

#if PLATFORM == WIN

        if (core->input.getButtonDown(Engine::InputCode::Mouse_Left)) {
#endif
            deltaX = core->input.getPointerDelta().x;
            deltaY = -core->input.getPointerDelta().y;
            // set cursor invisible
#if PLATFORM == WIN
        }
#endif

        cameraCtrl.ProcessInput(deltaX * 0.01f, deltaY * 0.01f, 0.0f);
        cameraCtrl.Update(dt);

        Engine::Camera::view(camera.view, cameraCtrl.m_position, cameraCtrl.m_up);
        camera.position = cameraCtrl.m_position;// TODO


        Engine::FrameBuffer::refreshScreen();


        glm::vec3 waterColor(0.1f, 0.3f, 0.9f);

        Engine::Shader::updateUniforms(shader, camera.projection, camera.view, model, camera.position, 
            waterColor, 5.0f, 0.5f, 2.5f, 0.1f, 0.1f, textureId0, textureId1);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        Engine::DrawCommand::draw(vao, meshData.indexBuffer.totalIndices, meshData.indexBuffer.indexElementType);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        //Engine::Shader::updateUniforms(planeShader, camera.projection, camera.view, planeTextureId);
        //Engine::DrawCommand::draw(planeVao, planeMeshData.indexBuffer.totalIndices, planeMeshData.indexBuffer.indexElementType);

    }

}