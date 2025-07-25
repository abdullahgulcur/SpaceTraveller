#pragma once

#include "OrbitCameraController.h"
#include "Universe.h"

namespace Game {

    class PlanetSceneTest {
    private:

        std::vector<PlanetColors> planetColors;

        glm::vec3 landColor0{ 32 / 255.f, 45 / 255.f, 18 / 255.f };
        glm::vec3 landColor1{ 93 / 255.f, 76 / 255.f, 31 / 255.f };
        glm::vec3 waterColor{ 0 / 255.f, 10 / 255.f, 39 / 255.f };
        glm::vec3 continentalShelfColor{ 0 / 255.f, 15 / 255.f, 131 / 255.f };
        float amountWater = 0.65f;
        float continentalShelf = 0.04f;
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
        float fresnelPowerClouds = 0.3f;
        float fresnelScaleClouds = 0.2f;
        float fresnelBiasClouds = 1.f;
        float fresnelPowerAtmosphere = 0.8f;
        float fresnelScaleAtmosphere = 0.15f;
        float fresnelBiasAtmosphere = 1.f;
        float specularStrength = 1.5f;
        float specularPower = 6.f;

        OrbitCameraController cameraCtrl;

    public:

        PlanetSceneTest() {}
        ~PlanetSceneTest() {}

        void init();
        void parsePlanetColors(std::vector<PlanetColors>& planetColors, const std::vector<unsigned char>& buffer);
        void start();
        void update(float dt);

    };
}