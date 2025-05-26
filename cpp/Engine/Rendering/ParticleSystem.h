#pragma once

#include "glm.hpp"
#include "Timer.h"

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

        //---------- GENERAL ---------- 

        template <typename T>
        void start(T& t, float time){
            t.particleCount = 0;
            t.particleStartTime = time;
            t.particleLastTriggerTime = 0.f;
        }

        //---------- SMOKE ---------- 

        template<std::size_t N>
        void reorder(ParticleSmoke<N>& p, float duration);

        template<std::size_t N>
        void update(ParticleSmoke<N>& p, float dt);

        template<std::size_t N>
        void fillInstanceData(ParticleSmoke<N>& p, ParticleGPUData* data);

        //---------- TUNNEL ---------- 

        template<std::size_t N>
        void reorder(ParticleTunnel<N>& p, float duration);

        template<std::size_t N>
        void update(ParticleTunnel<N>& p, float dt, float f);

        template<std::size_t N>
        void fillInstanceData(ParticleTunnel<N>& p, ParticleGPUData* data, glm::mat4& inverseView);

        //---------- SOLAR SYSTEMS ---------- 

        template<std::size_t N>
        void start(ParticleSolarSystems<N>& p, float time);

        template<std::size_t N>
        void update(ParticleSolarSystems<N>& p, float dt, float alpha);

        template<std::size_t N>
        void fillInstanceData(ParticleSolarSystems<N>& p, ParticleGPUData* data);

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


    }

}
