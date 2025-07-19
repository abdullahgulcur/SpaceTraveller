#include "pch.h"
#include "Universe.h"
#include "RandomValue.h"
#include "AssetManager.h"

namespace Game {

    void Universe::parsePlanetColors(std::vector<PlanetColors>& planetColors, const std::vector<unsigned char>& buffer) {

        std::string text(buffer.begin(), buffer.end());
        std::istringstream stream(text);
        std::string line;

        while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            int r0, g0, b0, r1, g1, b1, r2, g2, b2, r3, g3, b3;

            linestream >> r0 >> g0 >> b0 >> r1 >> g1 >> b1 >> r2 >> g2 >> b2 >> r3 >> g3 >> b3;

            PlanetColors colors;
            colors.landA = glm::u8vec3(r0, g0, b0);
            colors.landB = glm::u8vec3(r1, g1, b1);
            colors.sea = glm::u8vec3(r2, g2, b2);
            colors.shelf = glm::u8vec3(r3, g3, b3);

            planetColors.push_back(colors);
        }
    }

    void Universe::init() {


        std::vector<unsigned char> buffer;
        Engine::AssetManager assetManager;
        assetManager.readBytesFromAsset("data/planet_color_records.txt", buffer);
        Universe::parsePlanetColors(planetColors, buffer);

        for (int i = 0; i < solarSystemList.capacity(); i++) {
            SolarSystem solarSystem(i, glm::i16vec3(Engine::Random::randomPointInSphereShell(1.f, 32000)));
            solarSystemList.push(solarSystem);

            int planetCount = Engine::Random::random(4, 8);
            for (int j = 0; j < planetCount; j++) {
                //float offset = Engine::Random::randomFloat(0.5f, 1.f);
                Planet planet(j, i, Engine::Random::randomPointInCircleShell(30.f * (j + 1), 30.f * (j + 1)));

                PlanetColors& colors = planetColors[Engine::Random::random(0, planetColors.size() - 1)];
                planet.landColor0 = glm::vec3(colors.landA) / glm::vec3(255.f);
                planet.landColor1 = glm::vec3(colors.landB) / glm::vec3(255.f);
                planet.waterColor = glm::vec3(colors.sea) / glm::vec3(255.f);
                //planet.continentalShelfColor = glm::vec3(colors.shelf) / glm::vec3(255.f);
                planet.amountWater = Engine::Random::randomFloat(0.f, 0.8f);
                //planet.continentalShelf = Engine::Random::randomFloat(0.f, 0.4f);
                planet.landColorOverlay = Engine::Random::randomFloat(1.f, 2.f);
                planet.landColorPower = Engine::Random::randomFloat(1.f, 10.f);
                planet.surfaceTopologyScale = Engine::Random::randomFloat(0.1f, 1.f);
                planet.landColorBlendScale = Engine::Random::randomFloat(0.25f, 1.5f);
                planet.macroScale = Engine::Random::randomFloat(5.f, 15.f);
                /*planet.cloudScale = Engine::Random::randomFloat(1.f, 2.f);
                planet.cloudPower = Engine::Random::randomFloat(7.f, 20.f);
                planet.cloudOverlay = Engine::Random::randomFloat(0.f, 4.f);*/
                planet.fresnelPowerClouds = 0.3f;
                planet.fresnelScaleClouds = 0.2f;
                planet.fresnelBiasClouds = 1.f;
                planet.continentalShelf = 0.04f;

                /*planet.fresnelPowerAtmosphere = 0.8f;
                planet.fresnelScaleAtmosphere = 0.15f;
                planet.fresnelBiasAtmosphere = 1.f;*/
                planet.noiseOctaveTexIndex0 = Engine::Random::random(0, 6);
                planet.noiseOctaveTexIndex1 = Engine::Random::random(0, 6);
                //planet.noiseOctaveTexIndex2 = Engine::Random::random(0, 6);
                /*planet.specularStrength = 1.f;
                planet.specularPower = 1.f;*/

                //planet.landColor0 = Engine::Random::randomVec3(glm::vec3(0.f), glm::vec3(1.f));
                //planet.landColor1 = Engine::Random::randomVec3(glm::vec3(0.f), glm::vec3(1.f));
                //planet.amountSea = Engine::Random::randomFloat(0.f, 1.f);
                //planet.continentalShelf = Engine::Random::randomFloat(0.f, 0.1f);
                //planet.landColorOverlay = Engine::Random::randomFloat(0.f, 10.f);
                //planet.landColorPower = Engine::Random::randomFloat(0.f, 10.f);
                //planet.surfaceTopologyScale = Engine::Random::randomFloat(0.f, 3.f);
                //planet.landColorBlendScale = Engine::Random::randomFloat(0.1f, 5.f);
                //planet.macroScale = Engine::Random::randomFloat(0.5f, 5.f);
                //planet.cloudScale = Engine::Random::randomFloat(1.f, 2.f);
                //planet.cloudPower = Engine::Random::randomFloat(7.f, 20.f);
                //planet.cloudOverlay = Engine::Random::randomFloat(0.f, 4.f);
                //planet.fresnelPowerClouds = Engine::Random::randomFloat(0.f, 0.15f);
                //planet.fresnelScaleClouds = Engine::Random::randomFloat(0.f, 0.3f);
                //planet.fresnelPowerAtmosphere = Engine::Random::randomFloat(0.6f, 0.75f);
                //planet.fresnelScaleAtmosphere = Engine::Random::randomFloat(0.9f, 1.f);
                //planet.fresnelBiasAtmosphere = Engine::Random::randomFloat(0.9f, 0.95f);
                //planet.noiseOctaveTexIndex0 = Engine::Random::random(0, 1);
                //planet.noiseOctaveTexIndex1 = Engine::Random::random(0, 1);
                //planet.noiseOctaveTexIndex2 = Engine::Random::random(0, 1);

                planetList.push(planet);
            }
        }
    }
}