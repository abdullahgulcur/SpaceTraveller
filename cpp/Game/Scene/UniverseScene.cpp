#include "pch.h"
#include "UniverseScene.h"
#include "DrawCommand.h"
#include "FrameBuffer.h"
#include "Game.h"
#include "Vao.h"

namespace Game{

    void UniverseScene::init(){

        Game* game = Game::getInstance();
        Engine::ParticleSystem::ParticleGPUData gpuData[256];
        game->universe.fillGPUData(gpuData);
        Engine::VertexBuffer::generate(instanceBufferSolarSystems, 256 * sizeof(Engine::ParticleSystem::ParticleGPUData), &gpuData[0]);
        Engine::Vao::createParticleMeshVao(vaoBillboardSolarSystems, game->vertexBufferBillboard, instanceBufferSolarSystems);

    }

    void UniverseScene::start() {

    }

    void UniverseScene::update(float dt){

        Engine::Core* core = Engine::Core::getInstance();
        Game* game = Game::getInstance();

#if PLATFORM == WIN

        if (core->input.getButtonPress(Engine::InputCode::Space)) {

            
            game->tunnelEffectScene.start();
            game->sceneType = SceneType::TUNNEL_EFFECT;

        }
#endif


        Engine::Camera::Camera& camera = game->camera;

        Engine::Camera::perspectiveProjection(camera.projection, 90.0f, core->appSurface.getAspectRatio(), 0.1f, 1000.0f);

        Engine::FrameBuffer::refreshScreen();

        float deltaX = 0.f;
        float deltaY = 0.f;
        float scroll = 0.f;

#if PLATFORM == WIN

        if (core->input.getButtonDown(Engine::InputCode::Mouse_Left)) {
#endif
            deltaX = core->input.getPointerDelta().x;
            deltaY = -core->input.getPointerDelta().y;
#if PLATFORM == WIN
        }
#endif

        cameraCtrl.ProcessInput(deltaX * 0.01f, deltaY * 0.01f, 0.0f);
        cameraCtrl.Update(dt);

        Engine::Camera::view(camera.view, cameraCtrl.m_position, cameraCtrl.m_up);

        glm::mat4 projectionView = camera.projection * camera.view;
        glm::vec3 cameraRight;
        glm::vec3 cameraUp;
        Engine::Camera::getCameraRightAndUp(camera.view, cameraRight, cameraUp);

        Engine::Shader::updateUniforms(game->shaderProgram, projectionView, cameraRight, cameraUp);

        Engine::DrawCommand::drawQuadsInstanced(vaoBillboardSolarSystems, game->universe.solarSystemList.size());
    }

}