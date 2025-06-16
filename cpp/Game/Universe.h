#pragma once

#include "glm.hpp"
#include "ParticleSystem.h"

namespace Game {

    struct SolarSystem {
        unsigned short id;
        glm::i16vec3 position;

        SolarSystem() {}
        SolarSystem(unsigned short id, glm::i16vec3 position) :
            id(id), position(position) {}
    };

    struct Sun {
        unsigned short id = -1;
        glm::i16vec3 position;
        Sun() {}
        Sun(unsigned short id, glm::i16vec3 position) :
            id(id), position(position) {}
    };

    struct Planet {
        glm::vec3 relativePosition;
        unsigned short id;
        unsigned short solarSystemId;

        Planet() {}
        Planet(unsigned short id, unsigned short solarSystemId, glm::vec3 relativePosition) :
            relativePosition(relativePosition), id(id), solarSystemId(solarSystemId) {}
    };

    struct Satellite {
        glm::vec3 relativePosition;
        unsigned short id;
        unsigned short planetId;

        Satellite() {}
        Satellite(unsigned short id, unsigned short planetId, glm::vec3 relativePosition) :
            relativePosition(relativePosition), id(id), planetId(planetId) {}
    };

    class Universe {
    private:


    public:

        StaticArray<SolarSystem, 256> solarSystemList;
        StaticArray<Planet, 2048> planetList;
        StaticArray<Satellite, 4096> satelliteList;

        Universe() {}
        ~Universe() {}

        void init();
    };
}