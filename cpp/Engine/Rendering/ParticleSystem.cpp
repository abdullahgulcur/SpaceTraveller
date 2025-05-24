#include "pch.h"
#include "ParticleSystem.h"
#include "Core.h"
#include "VertexBuffer.h"
#include "DrawCommand.h"
#include "RandomValue.h"
#include "Algebra.h"

namespace Engine{

    namespace ParticleSystem{

        template void updateParticle<256>(ParticleSmoke<256>&, float);
        template void fillInstanceData<256>(ParticleSmoke<256>&, ParticleGPUData*);


        bool shouldTrigger(float& lastTriggerTime, float duration, float interval){
            float elapsed = duration - lastTriggerTime;
            if (elapsed >= interval) {
                lastTriggerTime = duration;
                return true;
            }
            return false;
        }

        template<std::size_t N>
        void reorderParticle(ParticleSmoke<N>& p, float duration) {
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
        void updateParticle(ParticleSmoke<N>& p, float dt) {

            float duration = static_cast<float>(Core::getInstance()->systemTimer.getTotalSeconds()) - p.particleStartTime;

            reorderParticle(p, duration);

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

    }

}