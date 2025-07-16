#pragma once

#include "glm.hpp"
#include "ParticleSystem.h"

namespace Game {

    struct PlanetColors {
        glm::u8vec3 landA;
        glm::u8vec3 landB;
        glm::u8vec3 sea;
        glm::u8vec3 shelf;
    };

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

        glm::vec3 landColor0{ 32 / 255.f, 45 / 255.f, 18 / 255.f };
        glm::vec3 landColor1{ 93 / 255.f, 76 / 255.f, 31 / 255.f };
        glm::vec3 waterColor{ 0 / 255.f, 10 / 255.f, 39 / 255.f };
        glm::vec3 continentalShelfColor{ 0 / 255.f, 15 / 255.f, 131 / 255.f };
        float amountWater = 0.65f;
        float continentalShelf = 0.05f;
        float surfaceTopologyScale = 0.13f;
        int noiseOctaveTexIndex0 = 0;
        int noiseOctaveTexIndex1 = 0;
        int noiseOctaveTexIndex2 = 0;
        float landColorOverlay = 2.45f;
        float landColorPower = 2.62f;
        float landColorBlendScale = 0.5f;
        float macroScale = 3.0f;
        float cloudScale = 0.2f;
        float cloudPower = 15.0f;
        float cloudOverlay = 3.2f;
        float cloudOpacity = 1.0f;
        glm::vec3 cloudColor{ 255 / 255.f,  255 / 255.f,  255 / 255.f };
        float fresnelPowerClouds = 0.1f;
        float fresnelScaleClouds = 0.15f;
        float fresnelBiasClouds = 1.0f;
        float fresnelPowerAtmosphere = 0.65f;
        float fresnelScaleAtmosphere = 1.f;
        float fresnelBiasAtmosphere = 0.9f;
        float specularStrength = 1.5;
        float specularPower = 6.0;

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

        std::vector<PlanetColors> planetColors;

        Universe() {}
        ~Universe() {}

        void parsePlanetColors(std::vector<PlanetColors>& planetColors, const std::vector<unsigned char>& buffer);

        void init();
    };
}