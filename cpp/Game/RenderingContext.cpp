#include "pch.h"
#include "RenderingContext.h"
#include "DrawCommand.h"
#include "Shader.h"
#include "FrameBuffer.h"
#include "Game.h"

#include "stb_image_write.h"

namespace Game {

    void RenderingContext::init() {

    }

    void RenderingContext::update() {

        RenderingContext::generateTextures();

        {
            std::unique_lock<std::mutex> lock(newFrameMutex);
            newFrameCV.wait(lock, [this] { return readyForNewFrame; });
            readyForNewFrame = false;
        }

        {
            std::lock_guard<std::mutex> lock(queueMutex);
            renderingQueueIndex = lastFilledQueueIndex;
        }

        RenderingContext::draw();
    }

    void RenderingContext::draw() {

        Game* game = Game::getInstance();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);


        glm::ivec2 screenSize;
        game->appSurface.getScreenSize(screenSize);

        glViewport(0, 0, screenSize.x, screenSize.y);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //glEnable(GL_DEPTH_TEST);
        //glDepthFunc(GL_LESS);

        //glEnable(GL_CULL_FACE);
        //glCullFace(GL_BACK);
        //glFrontFace(GL_CCW);

        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE);


        if (bufferDataStars.any(renderingQueueIndex)) {
            Shader::updateUniforms(game->assetGenerator.shaderParticleSolarSystem, bufferDataStars.shaderDataParticleSolarSystem[renderingQueueIndex]);
            glEnable(GL_BLEND);
            glDepthMask(GL_FALSE);
            Engine::DrawCommand::drawQuadsInstanced(game->assetGenerator.vaoParticleSolarSystem, bufferDataStars.gpuData[renderingQueueIndex].size(),
                game->assetGenerator.instanceBufferParticleDynamic, sizeof(ParticleSystem::ParticleGPUDataSolarSystem), &bufferDataStars.gpuData[renderingQueueIndex][0]);
            glDisable(GL_BLEND);
            glDepthMask(GL_TRUE);
        }

        if (bufferDataSolarSystem.any(renderingQueueIndex)) {
            for (int i = 0; i < bufferDataSolarSystem.shaderDataPlanet[renderingQueueIndex].size(); i++) {
                Shader::updateUniforms(game->assetGenerator.planetShader, bufferDataSolarSystem.shaderDataPlanet[renderingQueueIndex][i]);
                Engine::DrawCommand::draw(game->assetGenerator.vaoSphereMesh, game->assetGenerator.sphereMeshData.indexBuffer.totalIndices, game->assetGenerator.sphereMeshData.indexBuffer.indexElementType);
            }
        }

        if (bufferDataTerrainClipmaps.any(renderingQueueIndex)) {
            if (bufferDataTerrainClipmaps.gpuData[renderingQueueIndex].size()) {

                //std::vector<unsigned char> pixels(1024 * 1024);
                //glBindTexture(GL_TEXTURE_2D, bufferDataTerrainClipmaps.shaderDataTerrain[renderingQueueIndex].heightmap);
                //glGetTexImage(GL_TEXTURE_2D, 0, GL_RED, GL_UNSIGNED_BYTE, pixels.data());
                //stbi_write_png("outputtt.png", 1024, 1024, 1, pixels.data(), 1024);

                Shader::updateUniforms(game->assetGenerator.shaderTerrain, bufferDataTerrainClipmaps.shaderDataTerrain[renderingQueueIndex]);
                Engine::VertexBuffer::bufferSubData(game->assetGenerator.instanceBufferTerrain, 0, bufferDataTerrainClipmaps.gpuData[renderingQueueIndex].size() * sizeof(TerrainGPUData), &bufferDataTerrainClipmaps.gpuData[renderingQueueIndex][0]);
                //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                Engine::DrawCommand::drawInstanced(game->assetGenerator.vaoTerrainBlock, game->assetGenerator.terrainBlockMeshData.indexBuffer.totalIndices, game->assetGenerator.terrainBlockMeshData.indexBuffer.indexElementType, bufferDataTerrainClipmaps.gpuData[renderingQueueIndex].size());
                //glPolygonMode(GL_BACK, GL_FILL);
            }
        }
    }

    void RenderingContext::generateTextures() {


        if (terrainHeightmapGeneratorJobSystem.has()) {

            Game* game = Game::getInstance();

            game->assetGenerator.fbo.bind();

            glViewport(0, 0, 1024, 1024);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            Engine::Shader::bind(game->assetGenerator.shaderTerrainHeightmapGenerator.programId);

            terrainHeightmapGeneratorJobSystem.drawData[0].tex = game->assetGenerator.noiseTexture;

            Shader::updateUniforms(game->assetGenerator.shaderTerrainHeightmapGenerator, terrainHeightmapGeneratorJobSystem.drawData[0]);

            Engine::DrawCommand::drawQuad(game->assetGenerator.quadVAO);

            Engine::Shader::unbind();

            ////std::vector<unsigned char> pixels(1024 * 1024);
            ////glBindTexture(GL_TEXTURE_2D, heightmapTextureId);
            ////glGetTexImage(GL_TEXTURE_2D, 0, GL_RED, GL_UNSIGNED_BYTE, pixels.data());
            ////stbi_write_jpg("outputtt.jpg", 1024, 1024, 1, pixels.data(), 100);

            game->assetGenerator.fbo.unbind();

            terrainHeightmapGeneratorJobSystem.reset();
        }
    }

    void RenderingContext::setSimulationBufferIndex() {
        std::lock_guard<std::mutex> lock(queueMutex);
        for (int i = 0; i < 3; i++) {
            if (i != renderingQueueIndex && i != lastFilledQueueIndex) {
                simulationBufferIndex = i;
                RenderingContext::cleanBuffers();
                break;
            }
        }
    }

    void RenderingContext::setLastFilledBufferIndex() {
        std::lock_guard<std::mutex> lock(queueMutex);
        lastFilledQueueIndex = simulationBufferIndex;

        {
            std::lock_guard<std::mutex> lock_(newFrameMutex);
            readyForNewFrame = true;
        }
        newFrameCV.notify_one();

        //std::cout << "Sim End, Queue " << queueIndex << std::endl;
    }

    void RenderingContext::cleanBuffers() {

        //bufferDataStars.isActive[simulationBufferIndex] = false;
        //bufferDataSolarSystem.isActive[simulationBufferIndex] = false;
        //bufferDataTerrainClipmaps.isActive[simulationBufferIndex] = false;

        bufferDataStars.gpuData[simulationBufferIndex].clean();
        bufferDataSolarSystem.shaderDataPlanet[simulationBufferIndex].clean();
        bufferDataTerrainClipmaps.gpuData[simulationBufferIndex].clean();
    }

    void RenderingContext::submit(Shader::ShaderDataPlanet& shaderDataPlanet) {
        //bufferDataSolarSystem.isActive[simulationBufferIndex] = true;
        bufferDataSolarSystem.shaderDataPlanet[simulationBufferIndex].push(shaderDataPlanet);
    }

    void RenderingContext::submit(Engine::TerrainGeometryManager& terrainGeometryManager, Shader::ShaderDataTerrain& shaderDataTerrain) {

        //bufferDataTerrainClipmaps.isActive[simulationBufferIndex] = true;
        bufferDataTerrainClipmaps.shaderDataTerrain[simulationBufferIndex] = shaderDataTerrain;

        for (int i = terrainGeometryManager.getStartClipmapLevel(); i < terrainGeometryManager.getTotalClipmapLevel(); i++) {
            for (int j = 0; j < 36; j++) {
                if ((!terrainGeometryManager.getIsInner(i, j) || i == terrainGeometryManager.getStartClipmapLevel()) &&
                    !terrainGeometryManager.getOutOfBorder(i, j))
                    bufferDataTerrainClipmaps.gpuData[simulationBufferIndex].push(TerrainGPUData(glm::u8vec2(terrainGeometryManager.getBlockIndexWorldSpace(i, j)), i));
            }
        }

    }

    void RenderingContext::setBeforeSim() {
        Game::getInstance()->renderingContext.setSimulationBufferIndex();
    }

    void RenderingContext::setAfterSim() {
        Game::getInstance()->renderingContext.setLastFilledBufferIndex();
    }

}