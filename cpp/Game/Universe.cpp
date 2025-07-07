#include "pch.h"
#include "Universe.h"
#include "RandomValue.h"

namespace Game {

    void Universe::init() {

        for (int i = 0; i < solarSystemList.capacity(); i++) {
            SolarSystem solarSystem(i, glm::i16vec3(Engine::Random::randomPointInSphereShell(1.f, 32000)));
            solarSystemList.push(solarSystem);

            int planetCount = Engine::Random::random(5, 8);
            for (int j = 0; j < planetCount; j++) {
                float offset = Engine::Random::randomFloat(0.5f, 1.f);
                Planet planet(j, i, Engine::Random::randomPointInCircleShell(30.f * (j + 1) - offset, 30.f * (j + 1) + offset));

                planet.landColor0 = Engine::Random::randomVec3(glm::vec3(0.f), glm::vec3(1.f));
                planet.landColor1 = Engine::Random::randomVec3(glm::vec3(0.f), glm::vec3(1.f));
                planet.amountSea = Engine::Random::randomFloat(0.f, 1.f);
                planet.continentalShelf = Engine::Random::randomFloat(0.f, 0.1f);
                planet.landColorOverlay = Engine::Random::randomFloat(0.f, 10.f);
                planet.landColorPower = Engine::Random::randomFloat(0.f, 10.f);
                planet.surfaceTopologyScale = Engine::Random::randomFloat(0.f, 3.f);
                planet.landColorBlendScale = Engine::Random::randomFloat(0.1f, 5.f);
                planet.macroScale = Engine::Random::randomFloat(0.5f, 5.f);
                planet.cloudScale = Engine::Random::randomFloat(0.15f, 0.4f);
                planet.cloudPower = Engine::Random::randomFloat(7.f, 20.f);
                planet.cloudOverlay = Engine::Random::randomFloat(0.f, 4.f);
                planet.fresnelPowerClouds = Engine::Random::randomFloat(0.f, 0.15f);
                planet.fresnelScaleClouds = Engine::Random::randomFloat(0.f, 0.3f);
                planet.fresnelPowerAtmosphere = Engine::Random::randomFloat(0.6f, 0.75f);
                planet.fresnelScaleAtmosphere = Engine::Random::randomFloat(0.9f, 1.f);
                planet.fresnelBiasAtmosphere = Engine::Random::randomFloat(0.9f, 0.95f);
                planet.noiseOctaveTexIndex0 = Engine::Random::random(0, 1);
                planet.noiseOctaveTexIndex1 = Engine::Random::random(0, 1);
                planet.noiseOctaveTexIndex2 = Engine::Random::random(0, 1);

                planetList.push(planet);
            }
        }
    }
}