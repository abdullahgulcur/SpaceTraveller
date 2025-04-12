#pragma once

#include "glm.hpp"

namespace Engine{

    struct ParticleData {
        glm::vec3 position;
        float rotation;
        float scale;
        glm::vec4 color;
    };

    struct Particle{
        glm::vec3 position;
        float rotation;
        float scale;
        glm::vec4 color;

        // in a different linear buffer
        float time;
        float lifeTime;
        float angularVelocity;
        glm::vec3 force;
    };
}