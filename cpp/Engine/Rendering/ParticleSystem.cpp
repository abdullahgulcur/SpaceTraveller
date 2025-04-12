#include "pch.h"
#include "ParticleSystem.h"
#include "Core.h"
#include "VertexBuffer.h"
#include "DrawCommand.h"
#include "RandomValue.h"

namespace Engine{

    namespace ParticleSystem{

        ParticleSystem::ParticleSystem() {
            startTime = static_cast<float>(Core::getInstance()->systemTimer.getTotalSeconds());
            lastTriggerTime = startTime;
        }

        void ParticleSystem::update(float dt){

            float duration = static_cast<float>(Core::getInstance()->systemTimer.getTotalSeconds()) - startTime;

            // reorder particle data
            int i = 0;
            int count = static_cast<int>(particleCount);
            int last = count - 1;
            while (i <= last) {
                if (duration - particleSimulationData[i].startTime > particleSimulationData[i].lifeTime) {
                    particleData[i] = particleData[last];
                    particleSimulationData[i] = particleSimulationData[last];
                    last--;
                } else {
                    i++;
                }
            }
            particleCount = last + 1;

            // add new particle if triggers
            if(shouldTrigger(duration, 0.0001)){
                unsigned int index = particleCount++;

                particleSimulationData[index].startTime = duration;
                particleSimulationData[index].lifeTime = Random::randomFloat(3,7);
                particleSimulationData[index].angularVelocity = Random::randomFloat(10,360);
                particleSimulationData[index].force = Random::randomVec3(glm::vec3(15,15,15), glm::vec3(-15,-15,-15));

                ParticleData pd;
                pd.position = glm::vec3(0);
                pd.rotation = 0.0;
                pd.scale = Random::randomFloat(0.2,0.7);
                pd.color = glm::vec4(Random::randomVec3(glm::vec3(0,0,0), glm::vec3(1,1,1)), 1);

                particleData[index] = pd;
            }

            // update particle data
            for(int i = 0; i < particleCount; i++){
                float durationParticle = duration - particleSimulationData[i].startTime;
                forceOverLifetime(particleData[i].position, particleSimulationData[i].force, durationParticle, particleSimulationData[i].lifeTime, dt);
                rotationOverLifetime(particleData[i].rotation, 0.5, 0.1, durationParticle, particleSimulationData[i].lifeTime, dt);
                //forceOverLifetime(particleData[i].position, glm::vec3(0,-9.91, 0), durationParticle, particleSimulationData[i].lifeTime, dt);
            }

        }

        bool ParticleSystem::shouldTrigger(float duration, float interval){
            float elapsed = duration - lastTriggerTime;
            if (elapsed >= interval) {
                lastTriggerTime = duration;
                return true;
            }
            return false;
        }
    }

}