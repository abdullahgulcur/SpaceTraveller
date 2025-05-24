#include "pch.h"
#include "Universe.h"
#include "RandomValue.h"

namespace Game {

    void Universe::init() {

        for (int i = 0; i < solarSystemList.capacity(); i++) {

            SolarSystem ss;
            ss.id = i;
            ss.position = Engine::Random::randomPointInSphereShell(100.f, 200.f);
            solarSystemList.push(ss);
        }

        //std::vector<Engine::ParticleSystem::ParticleData> galaxyData;

        //for(int i = 0; i < MAX_GALAXIES; i++){
        //    Engine::ParticleSystem::ParticleData pd;
        //    pd.position = Engine::Random::randomVec3(glm::vec3(-10.f, -2.f, -30.f), glm::vec3(10.f,2.f,30.f));
        //    pd.rotation = Engine::Random::randomFloat(0.f, 360.f);
        //    pd.scale = Engine::Random::randomFloat(1.05f, 1.15f);
        //    pd.color = glm::vec4(1.f);// glm::vec4(Engine::Random::randomVec3(glm::vec3(1.0f, 0.6f, 0.6f), glm::vec3(1.f,0.5f,0.5f)), 1.f); // glm::vec4(1.f);//
        //    galaxyData.push_back(pd);
        //}

        //std::sort(galaxyData.begin(), galaxyData.end(), [](const Engine::ParticleSystem::ParticleData& a, const Engine::ParticleSystem::ParticleData& b) {
        //    return a.position.z > b.position.z;
        //});

        //unsigned int billboardMeshVertexBuffer;
        //Engine::VertexBuffer::generateBillboardVertexBuffer(billboardMeshVertexBuffer);

        //Engine::VertexBuffer::generate(galaxyInstanceBuffer, MAX_GALAXIES * sizeof(Engine::ParticleSystem::ParticleData), &galaxyData[0]);

        //Engine::Vao::createBillboardMeshVao(galaxyMeshVao, billboardMeshVertexBuffer, galaxyInstanceBuffer);
        //Engine::Shader::createShaderProgramParticleTextured(shaderProgram);
        //Engine::Texture::generateGalaxyFrameBufferTexture(texture2D, 256);
    }

    void Universe::fillGPUData(Engine::ParticleSystem::ParticleGPUData* gpuData) {

        for (int i = 0; i < solarSystemList.size(); i++) {

            Engine::ParticleSystem::ParticleGPUData pData;

            glm::vec3 position = solarSystemList[i].position;
            glm::vec3 intPart = glm::floor(position);
            glm::vec3 fracPart = (position - intPart) * 127.0f;

            pData.positionD = glm::i16vec3(intPart);
            pData.positionF = glm::i8vec3(fracPart);
            pData.scale = uint16_t((1.0f / 100.f) * 65535.0f);
            pData.rotation = uint8_t((0.f / (2.0f * 3.14159265359f)) * 255.0f);
            pData.color = glm::u8vec4(255);

            gpuData[i] = pData;
        }
    }

    //void fillInstanceData(ParticleSmoke<N>& p, ParticleGPUData* data) {

    //    for (int i = 0; i < p.particleCount; i++) {

    //        ParticleGPUData pData;

    //        glm::vec3 position(p.posX[i], p.posY[i], p.posZ[i]);
    //        glm::vec3 intPart = glm::floor(position);
    //        glm::vec3 fracPart = (position - intPart) * 127.0f;

    //        pData.positionD = glm::i16vec3(intPart);
    //        pData.positionF = glm::i8vec3(fracPart);
    //        pData.scale = uint16_t((p.scale[i] / 100.f) * 65535.0f);
    //        pData.rotation = uint8_t((p.rotation[i] / (2.0f * 3.14159265359f)) * 255.0f);
    //        pData.color = p.color[i];

    //        data[i] = pData;
    //    }
    //}

}