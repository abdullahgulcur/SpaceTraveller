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

        bool any(int index) {
            return gpuData[index].size() > 0;
        }
    };

    struct BufferDataSolarSystem {
        StaticArray<Shader::ShaderDataPlanet, 32> shaderDataPlanet[3]; // 32 parametre gibi olmasi lazim

        bool any(int index) {
            return shaderDataPlanet[index].size() > 0;
        }
    };

    struct BufferDataTerrainClipmaps {
        StaticArray<TerrainGPUData, 256> gpuData[3]; // TODO: 256 olarak kalamaz
        Shader::ShaderDataTerrain shaderDataTerrain[3];

        bool any(int index) {
            return gpuData[index].size() > 0;
        }
    };

    struct TerrainHeightmapGeneratorJobSystem {
        int drawIndex = 0;
        std::atomic<bool> hasJob;
        StaticArray<Shader::ShaderDataTerrainHeightmapGenerator, 16> drawData;

        bool has() {
            return hasJob;
        }

        void set() {
            hasJob = true;
        }

        void reset() {
            clean();
            hasJob = false;
        }

        void push(Shader::ShaderDataTerrainHeightmapGenerator data) {
            drawData.push(data);
        }

        void clean() {
            drawData.clean();
        }
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
        void generateTextures();
        void cleanBuffers();
        void setSimulationBufferIndex();
        void setLastFilledBufferIndex();

    public:

        // For drawing onto screen
        BufferDataStars bufferDataStars;
        BufferDataSolarSystem bufferDataSolarSystem;
        BufferDataTerrainClipmaps bufferDataTerrainClipmaps;

        // Texture generation
        TerrainHeightmapGeneratorJobSystem terrainHeightmapGeneratorJobSystem;

        RenderingContext() {}
        ~RenderingContext() {}
        void init();
        void update();
        
        static void setBeforeSim();
        static void setAfterSim();

        template<std::size_t N>
        void submit(ParticleSystem::ParticleSolarSystem<N>& p, Shader::ShaderDataParticleSolarSystem& shaderDataParticleSolarSystem) {

            //bufferDataStars.isActive[simulationBufferIndex] = true;
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