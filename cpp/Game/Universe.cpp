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
                planetList.push(planet);
            }
        }
    }
}