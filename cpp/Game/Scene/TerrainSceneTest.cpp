#include "pch.h"
#include "TerrainSceneTest.h"
#include "DrawCommand.h"
#include "FrameBuffer.h"
#include "Game.h"
#include "Vao.h"
#include "Core.h"
#include "VertexBuffer.h"

namespace Game {

    void TerrainSceneTest::init() {

    }

    void TerrainSceneTest::start() {

        cameraCtrl.init(Engine::Camera::CameraTransform(glm::vec3(1000.f, 50.f, 1000.f), -89.f, 0.f));
    }

    void TerrainSceneTest::update(float dt) {

        Engine::Core* core = Engine::Core::getInstance();
        Game* game = Game::getInstance();
        Engine::Input& input = core->input;
        Engine::Camera::Camera& camera = game->camera;

        if (input.getPointerDown()) {
            float deltaX = -input.getPointerDelta().x * 0.1f;
            float deltaY = input.getPointerDelta().y * 0.1f;
            cameraCtrl.addTargetPitch(deltaY);
            cameraCtrl.addTargetYaw(deltaX);
        }

#if PLATFORM == WIN
        if (input.getButtonDown(Engine::InputCode::W))
            cameraCtrl.targetTransform.position = cameraCtrl.getPosition() + cameraCtrl.getForward() * 30.f;

        if (input.getButtonDown(Engine::InputCode::S))
            cameraCtrl.targetTransform.position = cameraCtrl.getPosition() - cameraCtrl.getForward() * 30.f;

        if (input.getButtonDown(Engine::InputCode::D))
            cameraCtrl.targetTransform.position = cameraCtrl.getPosition() + cameraCtrl.getRight() * 30.f;

        if (input.getButtonDown(Engine::InputCode::A))
            cameraCtrl.targetTransform.position = cameraCtrl.getPosition() - cameraCtrl.getRight() * 30.f;

        if (input.getButtonDown(Engine::InputCode::E))
            cameraCtrl.targetTransform.position = cameraCtrl.getPosition() + cameraCtrl.getUp() * 30.f;

        if (input.getButtonDown(Engine::InputCode::Q))
            cameraCtrl.targetTransform.position = cameraCtrl.getPosition() - cameraCtrl.getUp() * 30.f;
#endif

        cameraCtrl.update(dt);

        Engine::Camera::lookAt(camera, cameraCtrl.getPosition(), cameraCtrl.getPosition() + cameraCtrl.getForward(), glm::vec3(0.f, 1.f, 0.f));

        Engine::FrameBuffer::refreshScreen();


        struct TerrainGPUData {
            glm::u8vec2 position;
            unsigned char level;
            TerrainGPUData() {}
            TerrainGPUData(glm::u8vec2 position, unsigned char level) : position(position), level(level) {}
        };
        std::vector<TerrainGPUData> instanceArray;

        Engine::Shader::updateUniforms(game->shaderTerrain, camera.projectionView, camera.position, 16);

        for (int i = game->terrainGeometryManager.startClipmapLevel; i < game->terrainGeometryManager.totalClipmapLevel; i++) {
            for (int j = 0; j < 36; j++) {
                if ((!game->terrainGeometryManager.getIsInner(i, j) || i == game->terrainGeometryManager.startClipmapLevel) &&
                    !game->terrainGeometryManager.getOutOfBorder(i, j))
                    instanceArray.push_back(TerrainGPUData(glm::u8vec2(game->terrainGeometryManager.getBlockIndexWorldSpace(i, j)), i));
            }
        }


        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        if (instanceArray.size()) {
            Engine::VertexBuffer::bufferSubData(game->instanceBufferTerrain, 0, instanceArray.size() * sizeof(TerrainGPUData), &instanceArray[0]);
            Engine::DrawCommand::drawInstanced(game->vaoTerrainBlock, game->terrainBlockMeshData.indexBuffer.totalIndices, game->terrainBlockMeshData.indexBuffer.indexElementType, instanceArray.size());
        }

        //glPolygonMode(GL_BACK, GL_FILL);

    }

}