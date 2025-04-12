#pragma once

#include "glm.hpp"

#include "Timer.h"
#include "Vao.h"
#include "VertexBuffer.h"

#define MAX_PARTICLES

namespace Engine{

    namespace ParticleSystem{

        // write all the necessary functions
        // you can make them templated in the future maybe
        // write just the most necessary ones first...

/*        template <typename Particle>
        void emission(Particle* particles, unsigned int particleCount, unsigned int rateOverTime, float time){

        }*/

        //void burst(Particle& particle, unsigned int count);
        inline void forceOverLifetime(glm::vec3& position, glm::vec3 force, float time, float lifeTime, float dt){
            position += force * dt;
        }

        //void forceOverLifetime(glm::vec3& position, glm::vec3 force0, glm::vec3 force1, float time, float lifeTime);
        void colorOverLifetime(glm::vec4& color, glm::vec3 col0, glm::vec3 col1, float time, float lifeTime);

        void sizeOverLifetimeConstant(float& size, float size0, float time, float lifeTime);
        void sizeOverLifetimeLinear(float& size, float size0, float size1, float time, float lifeTime);
        void sizeOverLifetimeCubic(float& size, float size0, float size1, float time, float lifeTime);

        inline void rotationOverLifetime(float& rotation, float angVel0, float angVel1, float time, float lifeTime, float dt){
            rotation += angVel0 * dt;
        }

        //void noise(Particle& particle, );
        //void OverLifetime(Particle& particle, );

        struct ParticleData {
            glm::vec3 position;
            float rotation;
            glm::vec4 color;
            float scale;
            int padding[7];
        };

        class ParticleSystem{

            // add velocity
            struct ParticleSimulationData {
                float startTime;
                float lifeTime;
                float angularVelocity;
                int padding0;
                glm::vec3 force;
                int padding1;
            };

        private:
        public:

            ParticleData particleData[8192];
            ParticleSimulationData particleSimulationData[8192];
            unsigned int particleCount = 0;
            float startTime;
            float lastTriggerTime;

            ParticleSystem();
            ~ParticleSystem() {}
            void update(float dt);
            bool shouldTrigger(float duration, float interval);

        };

    }

}
