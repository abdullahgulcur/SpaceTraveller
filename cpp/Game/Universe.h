#pragma once

#include "glm.hpp"
#include "ParticleSystem.h"

namespace Game {

    struct SolarSystem {
        unsigned int id;
        glm::vec3 position;
    };

    class Universe {
    private:


    public:

        StaticArray<SolarSystem, 256> solarSystemList;

        Universe() {}
        ~Universe() {}

        void init();
        void fillGPUData(Engine::ParticleSystem::ParticleGPUData* gpuData);
    };
}