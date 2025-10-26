#pragma once

#include "glm.hpp"
#include "Timer.h"
#include "RandomValue.h"

namespace Game {

    namespace ParticleSystem {

        struct ParticleGPUDataTunnelEffect {
            glm::i8vec3 position;
            unsigned char color;
        };

        struct ParticleGPUDataBurst {
            glm::i8vec3 position;
            glm::u8vec4 color;
            unsigned char scaleRotation;
        };

        struct ParticleGPUDataSolarSystem {
            glm::i16vec3 position;
            unsigned char alpha;
            unsigned char rotation;
        };

        struct ParticleGPUData {
            unsigned short scale;
            glm::i16vec3 positionD;
            glm::i8vec3 positionF;
            glm::u8vec4 color;
            unsigned char rotation;
        };

        template <std::size_t N>
        struct ParticleSmoke {
            float startTime[N];
            float lifeTime[N];

            float posX[N];
            float posY[N];
            float posZ[N];
            float scale[N];
            float rotation[N];
            glm::u8vec4 color[N];

            unsigned int particleCount = 0;
            float particleStartTime;
            float particleLastTriggerTime;
        };

        template <std::size_t N>
        struct ParticleTunnel {
            float startTime[N];
            float lifeTime[N];

            float posX[N];
            float posY[N];
            float posZ[N];
            float scale[N];
            glm::u8vec4 color[N];

            unsigned int particleCount = 0;
            float particleStartTime;
            float particleLastTriggerTime;
        };

        template <std::size_t N>
        struct ParticleSolarSystems {
            //float startTime[N];
            //float lifeTime[N];

            float posX[N];
            float posY[N];
            float posZ[N];
            float scale[N];
            float rotation[N];
            glm::u8vec4 color[N];

            unsigned int particleCount = 0;
            float particleStartTime;
            float particleLastTriggerTime;
        };

        template <std::size_t N>
        struct ParticleSolarSystem {

            unsigned short posX[N];
            unsigned short posY[N];
            unsigned short posZ[N];
            unsigned char rotation[N];
            unsigned char alpha[N];

            unsigned int particleCount = 0;
            bool anyUpdate;

            //float particleStartTime;
            //float particleLastTriggerTime;
        };

        //---------- GENERAL ---------- 

        inline bool shouldTrigger(float& lastTriggerTime, float duration, float interval) {
            float elapsed = duration - lastTriggerTime;
            if (elapsed >= interval) {
                lastTriggerTime = duration;
                return true;
            }
            return false;
        }

        template <typename T>
        void start(T& t, float time) {
            t.particleCount = 0;
            t.particleStartTime = time;
            t.particleLastTriggerTime = 0.f;
        }

        //---------- SMOKE ---------- 

        template<std::size_t N>
        void reorder(ParticleSmoke<N>& p, float duration) {
            int last = static_cast<int>(p.particleCount) - 1;
            int i = 0;
            while (i <= last) {
                if (duration - p.startTime[i] > p.lifeTime[i]) {
                    p.startTime[i] = p.startTime[last];
                    p.lifeTime[i] = p.lifeTime[last];
                    p.posX[i] = p.posX[last];
                    p.posY[i] = p.posY[last];
                    p.posZ[i] = p.posZ[last];
                    p.scale[i] = p.scale[last];
                    p.rotation[i] = p.rotation[last];
                    p.color[i] = p.color[last];
                    last--;
                }
                else
                    i++;
            }
            p.particleCount = last + 1;
        }

        template<std::size_t N>
        void update(ParticleSmoke<N>& p, float totalTime, float dt) {

            float duration = totalTime - p.particleStartTime;

            reorder(p, duration);

            // add new particle if triggers
            if (shouldTrigger(p.particleLastTriggerTime, duration, 0.01)) {
                unsigned int index = p.particleCount++;
                p.startTime[index] = duration;
                p.lifeTime[index] = 2.f;

                p.scale[index] = Engine::Random::randomFloat(0.1, 0.5);

                float angle = Engine::Random::randomFloat(0.f, 2.f * 3.14159265359f);
                float radius = 5.f; // Circle radius
                p.posX[index] = cos(angle) * radius;
                p.posY[index] = 0.f;
                p.posZ[index] = sin(angle) * radius;
                p.rotation[index] = 0.f;
                p.color[index] = glm::u8vec4(Engine::Random::random(0, 255), Engine::Random::random(0, 255), Engine::Random::random(0, 255), 255);
            }

            for (int i = 0; i < p.particleCount; i++) {

                float d = duration - p.startTime[i];
                p.posY[i] += dt * 5.f;
                p.rotation[i] += dt;
                p.color[i].a = (1 - glm::smoothstep(0.7f, 1.0f, d / p.lifeTime[i])) * 255;
            }
        }

        template<std::size_t N>
        void fillInstanceData(ParticleSmoke<N>& p, ParticleGPUData* data) {

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

        //---------- TUNNEL ---------- 

        template<std::size_t N>
        void reorder(ParticleTunnel<N>& p, float duration) {
            int last = static_cast<int>(p.particleCount) - 1;
            int i = 0;
            while (i <= last) {
                if (duration - p.startTime[i] > p.lifeTime[i]) {
                    p.startTime[i] = p.startTime[last];
                    p.lifeTime[i] = p.lifeTime[last];
                    p.posX[i] = p.posX[last];
                    p.posY[i] = p.posY[last];
                    p.posZ[i] = p.posZ[last];
                    p.scale[i] = p.scale[last];
                    p.color[i] = p.color[last];
                    last--;
                }
                else
                    i++;
            }
            p.particleCount = last + 1;
        }

        template<std::size_t N>
        void update(ParticleTunnel<N>& p, float totalTime, float dt, float f) {

            float duration = totalTime - p.particleStartTime;

            reorder(p, duration);

            // add new particle if triggers
            if (shouldTrigger(p.particleLastTriggerTime, duration, 0.001)) {
                unsigned int index = p.particleCount++;
                p.startTime[index] = duration;
                p.lifeTime[index] = 1.f;

                p.scale[index] = Engine::Random::randomFloat(0.05f, 0.1f);

                //float angle = Engine::Random::randomFloat(0.f, 2.f * 3.14159265359f);
                //float radius = sqrt(Random::randomFloat(0.f, 1.f)) * 5.f; // Uniform distribution
                //p.posX[index] = cos(angle) * radius;
                //p.posY[index] = 0.f;
                //p.posZ[index] = sin(angle) * radius;
                float angle = Engine::Random::randomFloat(0.f, 2.f * 3.14159265359f);
                float radius = 5.f; // Circle radius
                p.posX[index] = cos(angle) * radius;
                p.posY[index] = sin(angle) * radius;
                p.posZ[index] = -20.f;
                //p.rotation[index] = 0.f;
                p.color[index] = glm::u8vec4(255, 255, 255, 255);// glm::u8vec4(Random::random(0, 255), Engine::Random::random(0, 255), Engine::Random::random(0, 255), 255);
            }

            for (int i = 0; i < p.particleCount; i++) {

                float d = duration - p.startTime[i];
                p.posZ[i] += (f * 50 + 1.f) * dt;
                p.color[i].a = f * 255;
                //                p.rotation[i] += dt;
                                //p.color[i].a = (1 - glm::smoothstep(0.7f, 1.0f, d / p.lifeTime[i])) * 255;
            }
        }

        template<std::size_t N>
        void fillInstanceData(ParticleTunnel<N>& p, ParticleGPUData* data, glm::mat4& inverseView) {

            for (int i = 0; i < p.particleCount; i++) {

                ParticleGPUData pData;

                glm::vec3 position(p.posX[i], p.posY[i], p.posZ[i]);
                position = glm::vec3(inverseView * glm::vec4(position, 1.f));
                glm::vec3 intPart = glm::floor(position);
                glm::vec3 fracPart = (position - intPart) * 127.0f;

                pData.positionD = glm::i16vec3(intPart);
                pData.positionF = glm::i8vec3(fracPart);
                pData.scale = uint16_t((p.scale[i] / 100.f) * 65535.0f);
                //                pData.rotation = uint8_t((p.rotation[i] / (2.0f * 3.14159265359f)) * 255.0f);
                pData.color = p.color[i];

                data[i] = pData;
            }
        }

        //---------- SOLAR SYSTEMS ---------- 

        template<std::size_t N>
        void start(ParticleSolarSystems<N>& p, float totalTime) { // take positions as parameter

            p.particleCount = N;
            p.particleStartTime = totalTime;
            p.particleLastTriggerTime = p.particleStartTime;

            for (int i = 0; i < N; i++) {

                glm::vec3 position = Engine::Random::randomPointInSphereShell(100.f, 200.f);
                p.posX[i] = position.x;
                p.posY[i] = position.y;
                p.posZ[i] = position.z;

                p.scale[i] = Engine::Random::randomFloat(2.f, 3.f);

                p.rotation[i] = 0.f;
                p.color[i] = glm::u8vec4(255, 255, 255, 255);//glm::u8vec4(Random::random(0, 255), Engine::Random::random(0, 255), Engine::Random::random(0, 255), 255);

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
                //p.color[i] = glm::u8vec4(255, 255, 255, 255);//glm::u8vec4(Random::random(0, 255), Engine::Random::random(0, 255), Engine::Random::random(0, 255), 255);
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
