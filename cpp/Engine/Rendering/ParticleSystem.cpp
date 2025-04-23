#include "pch.h"
#include "ParticleSystem.h"
#include "Core.h"
#include "VertexBuffer.h"
#include "DrawCommand.h"
#include "RandomValue.h"
#include "Algebra.h"

namespace Engine{

    namespace ParticleSystem{

//        template <typename T>
//        void start(T& t){
//            t.startTime = static_cast<float>(Core::getInstance()->systemTimer.getTotalSeconds());
//            t.lastTriggerTime = t.startTime;
//        }

        bool shouldTrigger(float& lastTriggerTime, float duration, float interval){
            float elapsed = duration - lastTriggerTime;
            if (elapsed >= interval) {
                lastTriggerTime = duration;
                return true;
            }
            return false;
        }

        void reorderParticleTunnelEffect(ParticleTunnelEffect& p, float duration){
            int last = static_cast<int>(p.particleCount) - 1;
            int i = 0;
            while (i <= last) {
                if (duration - p.startTime[i] > p.lifeTime[i]) {



                    glm::vec2 a(0.f);
                    a = Algebra::linstep(a, a, a, a, a);

                    p.startTime[i] = p.startTime[last];
                    p.lifeTime[i] = p.lifeTime[last];
                    //p.velocity[i] = p.velocity[last];
                    p.posX[i] = p.posX[last];
                    p.posY[i] = p.posY[last];
                    p.posZ[i] = p.posZ[last];
                    p.scale[i] = p.scale[last];
                    last--;
                } else
                    i++;
            }
            p.particleCount = last + 1;
        }

        void updateParticleTunnelEffect(ParticleTunnelEffect& p, float dt){

            float duration = static_cast<float>(Core::getInstance()->systemTimer.getTotalSeconds()) - p.particleStartTime;

            reorderParticleTunnelEffect(p, duration);

            // add new particle if triggers
            if(shouldTrigger(p.particleLastTriggerTime, duration, 0.001)){
                unsigned int index = p.particleCount++;
                p.startTime[index] = duration;
                p.lifeTime[index] = 1.f;//Algebra::linstep(duration, 0.f, 3.f, 3.f, 1.0f) ;
                //p.velocityOffset[index] = 0.f;//Random::randomFloat(0,10);
                p.scale[index] = Random::randomFloat(0.02,0.05);

                p.posX[index] = Random::randomFloat(-3.f,3.f);
                p.posY[index] = Random::randomFloat(-6.f,6.f);
                p.posZ[index] = 0.f;
            }

            //p.force = duration < 3.0f ? 0.3f : 0.f;

            // update particle data
            for(int i = 0; i < p.particleCount; i++){
                //p.velocity += p.force * dt;
                //p.velocity[i] += p.force * dt;
                p.posZ[i] += p.velocity * dt;
            }

            // update gpu data
            for(int i = 0; i < p.particleCount; i++){
                p.gpuData[i*4+0] = p.posX[i];
                p.gpuData[i*4+1] = p.posY[i];
                p.gpuData[i*4+2] = p.posZ[i];
                p.gpuData[i*4+3] = p.scale[i];
            }

        }






//------------------------------------------------------------------------------------------------
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
                //particleSimulationData[index].force = Random::randomVec3(glm::vec3(50,50,-100), glm::vec3(-50,-50,-150));
                particleSimulationData[index].force = Random::randomVec3(glm::vec3(10,-10,10), glm::vec3(-10,-10,-10));
                particleSimulationData[index].velocity = glm::vec3(0,10,0);


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
                forceOverLifetimeConstant(particleSimulationData[i].velocity, particleSimulationData[i].force, dt);
                rotationOverLifetimeConstant(particleData[i].rotation, 0.5, dt);
                velocityOverLifetimeConstant(particleData[i].position, particleSimulationData[i].velocity, dt);
                //colorOverLifetimeLinear(particleData[i].color, )
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