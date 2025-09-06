#include "pch.h"
#include "ParticleSystem.h"
#include "Game.h"

namespace Game{

    namespace ParticleSystem{


        //---------- SOLAR SYSTEMS ---------- 

        template<std::size_t N>
        void start(ParticleSolarSystems<N>& p) { // take positions as parameter

            p.particleCount = N;
            p.particleStartTime = Game::getInstance()->systemTimer.getTotalSeconds();
            p.particleLastTriggerTime = p.particleStartTime;

            for (int i = 0; i < N; i++) {

                glm::vec3 position = Engine::Random::randomPointInSphereShell(100.f, 200.f);
                p.posX[i] = position.x;
                p.posY[i] = position.y;
                p.posZ[i] = position.z;

                p.scale[i] = Random::randomFloat(2.f, 3.f);

                p.rotation[i] = 0.f;
                p.color[i] = glm::u8vec4(255, 255, 255, 255);//glm::u8vec4(Random::random(0, 255), Random::random(0, 255), Random::random(0, 255), 255);

            }

        }

        template<std::size_t N>
        void update(ParticleSolarSystems<N>& p, float dt, float alpha) {

            for (int i = 0; i < N; i++) {

                unsigned char a = alpha * 255;
                p.color[i] = glm::u8vec4(255, 255, 255, a);

            }
        }

        template<std::size_t N>
        void fillInstanceData(ParticleSolarSystems<N>& p, ParticleGPUData* data) {

            for (int i = 0; i < p.particleCount; i++) {

                ParticleGPUData pData;

                glm::vec3 position(p.posX[i], p.posY[i], p.posZ[i]);
                glm::vec3 intPart = glm::floor(position);
                glm::vec3 fracPart = (position - intPart) * 127.0f;

                pData.positionD = glm::i16vec3(intPart);
                pData.positionF = glm::i8vec3(fracPart);
                pData.scale = uint16_t((p.scale[i] / 100.f) * 65535.0f);
                pData.rotation = uint8_t((p.rotation[i] / (2.0f * 3.14159265359f)) * 255.0f);
                pData.color = p.color[i];

                data[i] = pData;
            }
        }

        //---------- SOLAR SYSTEM ---------- 

        template<std::size_t N>
        void start(ParticleSolarSystem<N>& p, glm::i16vec3* positions) {

            p.particleCount = N;

            for (int i = 0; i < N; i++) {
                glm::i16vec3 position = positions[i];
                p.posX[i] = position.x;
                p.posY[i] = position.y;
                p.posZ[i] = position.z;
                p.rotation[i] = 0;// unsigned char((Random::randomFloat(0.f, 360.f) / (2.0f * 3.14159265359f)) * 255.0f);
                p.alpha[i] = 255;
                //p.color[i] = glm::u8vec4(255, 255, 255, 255);//glm::u8vec4(Random::random(0, 255), Random::random(0, 255), Random::random(0, 255), 255);
            }

        }

        template<std::size_t N>
        void update(ParticleSolarSystem<N>& p, float alpha) {

            for (int i = 0; i < N; i++) {
                unsigned char a = alpha * 255;
                p.alpha[i] = a;
            }
        }

        template<std::size_t N>
        void fillInstanceData(ParticleSolarSystem<N>& p, ParticleGPUDataSolarSystem* data) {

            for (int i = 0; i < p.particleCount; i++) {

                ParticleGPUDataSolarSystem pData;
                glm::i16vec3 position(p.posX[i], p.posY[i], p.posZ[i]);
                pData.position = position;
                pData.rotation = p.rotation[i];
                pData.alpha = p.alpha[i];
                data[i] = pData;
            }
        }
    }

}