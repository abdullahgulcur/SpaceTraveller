#include "pch.h"
#include "ParticleSystem.h"
#include "Core.h"
#include "VertexBuffer.h"
#include "DrawCommand.h"
#include "RandomValue.h"
#include "Algebra.h"

namespace Engine{

    namespace ParticleSystem{

        template void update<256>(ParticleSmoke<256>&, float);
        template void fillInstanceData<256>(ParticleSmoke<256>&, ParticleGPUData*);

        template void update<1024>(ParticleTunnel<1024>&, float, float);
        template void fillInstanceData<1024>(ParticleTunnel<1024>&, ParticleGPUData*, glm::mat4&);

        template void start<128>(ParticleSolarSystems<128>&, float);
        template void update<128>(ParticleSolarSystems<128>&, float, float);
        template void fillInstanceData<128>(ParticleSolarSystems<128>&, ParticleGPUData*);

        bool shouldTrigger(float& lastTriggerTime, float duration, float interval){
            float elapsed = duration - lastTriggerTime;
            if (elapsed >= interval) {
                lastTriggerTime = duration;
                return true;
            }
            return false;
        }

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
        void update(ParticleSmoke<N>& p, float dt) {

            float duration = static_cast<float>(Core::getInstance()->systemTimer.getTotalSeconds()) - p.particleStartTime;

            reorder(p, duration);

            // add new particle if triggers
            if (shouldTrigger(p.particleLastTriggerTime, duration, 0.01)) {
                unsigned int index = p.particleCount++;
                p.startTime[index] = duration;
                p.lifeTime[index] = 2.f;

                p.scale[index] = Random::randomFloat(0.1, 0.5);

                //float angle = Random::randomFloat(0.f, 2.f * 3.14159265359f);
                //float radius = sqrt(Random::randomFloat(0.f, 1.f)) * 5.f; // Uniform distribution
                //p.posX[index] = cos(angle) * radius;
                //p.posY[index] = 0.f;
                //p.posZ[index] = sin(angle) * radius;
                float angle = Random::randomFloat(0.f, 2.f * 3.14159265359f);
                float radius = 5.f; // Circle radius
                p.posX[index] = cos(angle) * radius;
                p.posY[index] = 0.f;
                p.posZ[index] = sin(angle) * radius;
                p.rotation[index] = 0.f;
                p.color[index] = glm::u8vec4(Random::random(0, 255), Random::random(0, 255), Random::random(0, 255), 255);
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
        void update(ParticleTunnel<N>& p, float dt, float f) {

            float duration = static_cast<float>(Core::getInstance()->systemTimer.getTotalSeconds()) - p.particleStartTime;

            reorder(p, duration);

            // add new particle if triggers
            if (shouldTrigger(p.particleLastTriggerTime, duration, 0.001)) {
                unsigned int index = p.particleCount++;
                p.startTime[index] = duration;
                p.lifeTime[index] = 1.f;

                p.scale[index] = Random::randomFloat(0.05f, 0.1f);

                //float angle = Random::randomFloat(0.f, 2.f * 3.14159265359f);
                //float radius = sqrt(Random::randomFloat(0.f, 1.f)) * 5.f; // Uniform distribution
                //p.posX[index] = cos(angle) * radius;
                //p.posY[index] = 0.f;
                //p.posZ[index] = sin(angle) * radius;
                float angle = Random::randomFloat(0.f, 2.f * 3.14159265359f);
                float radius = 5.f; // Circle radius
                p.posX[index] = cos(angle) * radius;
                p.posY[index] = sin(angle) * radius; 
                p.posZ[index] = -20.f;
                //p.rotation[index] = 0.f;
                p.color[index] = glm::u8vec4(255, 255, 255, 255);// glm::u8vec4(Random::random(0, 255), Random::random(0, 255), Random::random(0, 255), 255);
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
        void start(ParticleSolarSystems<N>& p, float time) { // take positions as parameter

            p.particleCount = N;
            p.particleStartTime = time;
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
    }

}