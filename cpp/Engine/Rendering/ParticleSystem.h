#pragma once

#include "glm.hpp"

#include "Timer.h"
#include "Vao.h"
#include "VertexBuffer.h"

namespace Engine{

    namespace ParticleSystem{

        struct ParticleGPUDataTunnelEffect {
            glm::i8vec3 position;
            unsigned char color;
        };

        struct ParticleGPUDataBurst {
            glm::i8vec3 position;
            glm::u8vec4 color;
            unsigned char scaleRotation;
        };

        struct ParticleGPUData {
            unsigned short scale;
            glm::i16vec3 positionD;
            glm::i8vec3 positionF;
            glm::u8vec4 color;
            unsigned char rotation;
        };

        //template <typename Size>
        struct ParticleSmoke {
            float startTime[4096];
            float lifeTime[4096];

            float posX[4096];
            float posY[4096];
            float posZ[4096];
            float scale[4096];
            float rotation[4096];
            glm::u8vec4 color[4096];

            ParticleGPUData gpuData[4096];

            unsigned int particleCount = 0;
            float particleStartTime;
            float particleLastTriggerTime;
        };

        //struct ParticleTunnelEffect {
        //    float startTime[1024];
        //    float lifeTime[1024];

        //    //float velocityOffset[1024];

        //    float posX[1024];
        //    float posY[1024];
        //    float posZ[1024];
        //    float scale[1024];

        //    float gpuData[1024*4];

        //    unsigned int particleCount = 0;
        //    float particleStartTime;
        //    float particleLastTriggerTime;
        //    float force;
        //    float velocity = 60.f;
        //};

        template <typename T>
        void start(T& t, unsigned int time){
            t.particleStartTime = time;//static_cast<float>(Core::getInstance()->systemTimer.getTotalSeconds());
            t.particleLastTriggerTime = t.particleStartTime;
        }


        //bool shouldTrigger(float duration, float interval);

        /*void reorderParticleTunnelEffect(ParticleTunnelEffect& p, float duration);
        void updateParticleTunnelEffect(ParticleTunnelEffect& p, float dt);*/

        //void update_(float dt);

        void reorderParticleSmoke(ParticleSmoke& p, float duration);
        void updateParticleSmoke(ParticleSmoke& p, float dt);

        //--------------------------------------------------------

        /*inline void velocityOverLifetimeConstant(glm::vec3& p, glm::vec3 v, float dt){
            p += v * dt;
        }

        inline void forceOverLifetimeConstant(glm::vec3& v, glm::vec3 f, float dt){
            v += f * dt;
        }

        inline void forceOverLifetimeLinear(glm::vec3& v, glm::vec3 f0, glm::vec3 f1, float time, float lifeTime, float dt){
            v += glm::mix(f0, f1, time / lifeTime) * dt;
        }

        inline void forceOverLifetimeCubic(glm::vec3& v, glm::vec3 f0, glm::vec3 f1, float time, float lifeTime, float dt){
            v += glm::smoothstep(f0, f1, glm::vec3(time / lifeTime)) * dt;
        }

        inline void colorOverLifetimeLinear(glm::vec3& c, glm::vec3 c0, glm::vec3 c1, float time, float lifeTime){
            c = glm::mix(c0, c1, time / lifeTime);
        }

        inline void colorOverLifetimeCubic(glm::vec3& c, glm::vec3 c0, glm::vec3 c1, float time, float lifeTime){
            c = glm::smoothstep(c0, c1, glm::vec3(time / lifeTime));
        }

        inline void sizeOverLifetimeLinear(float& s, float s0, float s1, float time, float lifeTime){
            s = glm::mix(s0, s1, time / lifeTime);
        }

        inline void sizeOverLifetimeCubic(float& s, float s0, float s1, float time, float lifeTime){
            s = glm::smoothstep(s0, s1, time / lifeTime);
        }

        inline void rotationOverLifetimeConstant(float& r, float v, float dt){
            r += v * dt;
        }*/

        //--------------------------------------------------------


        //struct ParticleData {
        //    glm::vec3 position; // common
        //    float rotation;
        //    glm::vec4 color;
        //    float scale;
        //    int padding[7];
        //};

        //class ParticleSystem{

        //    struct ParticleSimulationData {
        //        float startTime; // common
        //        float lifeTime; // common
        //        float angularVelocity;
        //        int padding0;
        //        glm::vec3 force;
        //        int padding1;
        //        glm::vec3 velocity;
        //        int padding2[5];
        //        // color0
        //        // color1
        //    };

        //private:
        //public:

        //    ParticleData particleData[8192];
        //    ParticleSimulationData particleSimulationData[8192];
        //    unsigned int particleCount = 0;
        //    float startTime;
        //    float lastTriggerTime;

        //    ParticleSystem();
        //    ~ParticleSystem() {}
        //    void update(float dt);
        //    bool shouldTrigger(float duration, float interval);

        //};

    }

}
