#pragma once

#include "Shader.h"
#include "ParticleSystem.h"

namespace Game {

    enum RenderQueueState {
        AVAILABLE = 0,
        BUSY = 1,
        READY = 2
    };

    class RenderingContext {
    private:

        int getQueueIndexForRendering();
        void setQueueAvailable(int queueIndex);
        int getQueueIndexForSimulation();
        void setQueueReadyForRendering(int queueIndex);

    public:

        RenderQueueState stateQueueList[3] = { RenderQueueState::AVAILABLE , RenderQueueState::AVAILABLE , RenderQueueState::AVAILABLE };
        int recentlyFilledQueueIndex = -1;
        std::mutex queueMutex;

        StaticArray<ParticleSystem::ParticleGPUDataSolarSystem, 256> gpuData[3];
        Shader::ShaderDataParticleSolarSystem shaderDataParticleSolarSystem[3];

        bool appClose = false;

        /*StaticArray<Shader::ShaderDataFXAA, 256> shaderDataListFXAA;
        StaticArray<Shader::ShaderDataParticle, 256> shaderDataListFXAA;
        StaticArray<Shader::ShaderDataParticleTextured, 256> shaderDataListFXAA;
        StaticArray<Shader::ShaderDataPlanet, 256> shaderDataListFXAA;
        StaticArray<Shader::ShaderDataSun, 256> shaderDataListFXAA;
        StaticArray<Shader::ShaderDataTerrain, 256> shaderDataListFXAA;
        StaticArray<Shader::ShaderDataTextureGeneratorSun, 256> shaderDataListFXAA;*/

        RenderingContext() {}
        ~RenderingContext() {}
        void renderMain();
        void init();
        void render();
        void fillRenderQueue(); // take render objects as parameter

    };
}