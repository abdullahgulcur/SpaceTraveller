#include "pch.h"
#include "RenderingContext.h"
#include "DrawCommand.h"
#include "Shader.h"
#include "FrameBuffer.h"
#include "Game.h"

namespace Game {

    void RenderingContext::init() {


    }

    void RenderingContext::update() {

        int queueIndex;
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            queueIndex = lastFilledQueueIndex;
            if (queueIndex == -1)
                return;
            renderingQueueIndex = queueIndex;
            //std::cout << "Rendering Start, Queue " << queueIndex << std::endl;
        }

        RenderingContext::draw();
    }

    void RenderingContext::draw() {

        Engine::FrameBuffer::bindFbo(0);
        glViewport(0, 0, 1560, 720); // TODO:
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glEnable(GL_DEPTH_TEST);

        Game* game = Game::getInstance();

        if (bufferDataStars.isActive) {
            Shader::updateUniforms(game->assetGenerator.shaderParticleSolarSystem, bufferDataStars.shaderDataParticleSolarSystem[renderingQueueIndex]);
            glEnable(GL_BLEND);
            glDepthMask(GL_FALSE);
            Engine::DrawCommand::drawQuadsInstanced(game->assetGenerator.vaoParticleSolarSystem, bufferDataStars.gpuData[renderingQueueIndex].size(),
                game->assetGenerator.instanceBufferParticleDynamic, sizeof(ParticleSystem::ParticleGPUDataSolarSystem), &bufferDataStars.gpuData[renderingQueueIndex][0]);
            glDisable(GL_BLEND);
            glDepthMask(GL_TRUE);
        }

        if (bufferDataSolarSystem.isActive) {

            for (int i = 0; i < bufferDataSolarSystem.shaderDataPlanet[renderingQueueIndex].size(); i++) {
                Shader::updateUniforms(game->assetGenerator.planetShader, bufferDataSolarSystem.shaderDataPlanet[renderingQueueIndex][i]);
                Engine::DrawCommand::draw(game->assetGenerator.vaoSphereMesh, game->assetGenerator.sphereMeshData.indexBuffer.totalIndices, game->assetGenerator.sphereMeshData.indexBuffer.indexElementType);
            }
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
        //std::cout << "Sim End, Queue " << queueIndex << std::endl;
    }

    void RenderingContext::cleanBuffers() {

        bufferDataStars.isActive[simulationBufferIndex] = false;
        bufferDataSolarSystem.isActive[simulationBufferIndex] = false;

        bufferDataStars.gpuData[simulationBufferIndex].clean();
        bufferDataSolarSystem.shaderDataPlanet[simulationBufferIndex].clean();
    }

    void RenderingContext::submit(Shader::ShaderDataPlanet& shaderDataPlanet) {
        bufferDataSolarSystem.isActive[simulationBufferIndex] = true;
        bufferDataSolarSystem.shaderDataPlanet[simulationBufferIndex].push(shaderDataPlanet);
    }



}