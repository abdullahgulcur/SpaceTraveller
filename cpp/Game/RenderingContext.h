#pragma once

#include "Shader.h"
#include "ParticleSystem.h"
#include "TerrainGeometryManager.h"

namespace Game {

    struct TerrainGPUData {
        glm::u8vec2 position;
        unsigned char level;
        TerrainGPUData() {}
        TerrainGPUData(glm::u8vec2 position, unsigned char level) : position(position), level(level) {}
    };

    struct BufferDataStars {
        StaticArray<ParticleSystem::ParticleGPUDataSolarSystem, 256> gpuData[3];
        Shader::ShaderDataParticleSolarSystem shaderDataParticleSolarSystem[3];
        //unsigned int vao; // const
        //unsigned int instanceBuffer; // const
        //unsigned int stride; // const
        bool isActive[3];
    };

    struct BufferDataSolarSystem {
        StaticArray<Shader::ShaderDataPlanet, 32> shaderDataPlanet[3]; // 32 parametre gibi olmasi laizm
        bool isActive[3];
    };

    struct BufferDataTerrainClipmaps {
        StaticArray<TerrainGPUData, 256> gpuData[3]; // TODO: 256 olarak kalamaz
        Shader::ShaderDataTerrain shaderDataTerrain[3];
        bool isActive[3];
    };

    class RenderingContext {
    private:

        std::mutex queueMutex;
        int lastFilledQueueIndex = -1;
        int renderingQueueIndex = -1;
        int simulationBufferIndex = -1;

        std::mutex newFrameMutex;
        std::condition_variable newFrameCV;
        bool readyForNewFrame = false;

        void draw();
        void cleanBuffers();
        void setSimulationBufferIndex();
        void setLastFilledBufferIndex();

    public:


        BufferDataStars bufferDataStars;
        BufferDataSolarSystem bufferDataSolarSystem;
        BufferDataTerrainClipmaps bufferDataTerrainClipmaps;

        RenderingContext() {}
        ~RenderingContext() {}
        void init();
        void update();
        
        static void setBeforeSim();
        static void setAfterSim();

        template<std::size_t N>
        void submit(ParticleSystem::ParticleSolarSystem<N>& p, Shader::ShaderDataParticleSolarSystem& shaderDataParticleSolarSystem) {

            bufferDataStars.isActive[simulationBufferIndex] = true;
            bufferDataStars.shaderDataParticleSolarSystem[simulationBufferIndex] = shaderDataParticleSolarSystem;

            for (int i = 0; i < p.particleCount; i++) {

                ParticleSystem::ParticleGPUDataSolarSystem pData;
                glm::i16vec3 position(p.posX[i], p.posY[i], p.posZ[i]);
                pData.position = position;
                pData.rotation = p.rotation[i];
                pData.alpha = p.alpha[i];
                bufferDataStars.gpuData[simulationBufferIndex].push(pData);
            }

        }

        void submit(Shader::ShaderDataPlanet& shaderDataPlanet);
        void submit(Engine::TerrainGeometryManager& terrainGeometryManager, Shader::ShaderDataTerrain& shaderDataTerrain);

        
    };
}